//
// Created by jackson on 17-3-12.
//

#include "EventLoop.h"
#include "../Base/Logger.h"
#include "../Net/Channel.h"
#include "Socketopts.h"

#include <sys/eventfd.h>
#include <csignal>

using namespace Mu;
using namespace Net;
//匿名命名空间　匿名空间内的数据只能在本文件内使用
//这和声明为static的全局名称的链接属性是相同的，即名称的作用域被限制在当前文件中，无法通过在另外的文件中使用extern声明来进行链接
//C++ 新的标准中提倡使用匿名命名空间,而不推荐使用static,因为static用在不同的地方,涵义不同,容易造成混淆.另外,static不能修饰class
namespace
{
    //线程局部变量　用来判断该线程是否已经运行着一个EventLoop
    __thread EventLoop *t_loopInThisThread = NULL;

    //轮询的超时时间　10000毫秒　＝　10秒
    const int kPollTimeMs = 10000;

    //创建eventfd,用来支持线程之间的通信
    //eventfd具体与pipe有点像，用来完成两个线程之间事件触发
    int createEventfd()
    {
        int evefd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
        if(evefd < 0)
        {
            LOG_SYSERR << "Failed in eventfd";
            abort();
        }
        return evefd;
    }


 // 这个类的作用是忽略管道事件
// 因为管道已经被使用另外的方法处理了
    class IgnorePipe
    {
    public:
        IgnorePipe()
        {
            ::signal(SIGPIPE, SIG_IGN);
        }
    };

    //一个全局变量，用于实现对SIGPIPE的忽略
    IgnorePipe initObj;
}

//静态函数
//返回当前线程的reactor对象的指针
EventLoop * EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}

//构造函数
EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      eventHandling_(false),
      callingPendingFunctors_(false),
      iteration_(0),
      threadId_(Mu::Base::CurrentThread::tid()),
      poller_(Poller::newDefaultPoller(this)),//采用默认的轮询器来创建轮询器
      timerQueue_(new TimerQueue(this)),
      wakeupFd_(createEventfd()),
      wakeupChannel_(new Channel(this, wakeupFd_)),
      currentChannel(NULL)
{
    LOG_DEBUG << "EventLoop created " << this << " in thread: " << threadId_;

    if(t_loopInThisThread)
    {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread << " exixt in "
                "this thread " << threadId_;
    }
    else
    {
        t_loopInThisThread = this;
    }

    //设置唤醒处理器的回调函数为EventLoop::handleRead函数
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
    //启动wakeupChannel的读功能
    wakeupChannel_->enableRead();
}

//析构函数,销毁对象并情理
EventLoop::~EventLoop()
{
    LOG_DEBUG << "EventLoop " << this << " of thread " << threadId_
              << " distructs in thread " << Mu::Base::CurrentThread::tid();
    //从EventLoop和poller中移除wakeupChannel
    wakeupChannel_->disableAll();
    wakeupChannel_->remove();
    //关闭通道
    ::close(wakeupFd_);
    t_loopInThisThread = NULL;
}

//Reactor主函数　循环等待POLLER返回并处理事件
void EventLoop::loop()
{
    //断言reactor还没有开始循环
    assert(!looping_);
    //判断loop在创建EventLoop的线程被调用
    assertInLoopThread();
    //设置循环开始标志
    looping_ = true;
    //设置循环结束标志为false
    quit_ = false;
    LOG_TRACE << "EventLoop " << this << " start looping";
    //进入循环
    while(!quit)
    {
        //情理已激活的事件处理器队列
        activeChannels_.clear();

        //开始轮询
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);

        //记录循环的次数
        ++ iteration_;
        if(Mu::Base::Logger::Loglevel() <= Mu::Base::Logger::TRACE)
        {
            printActiveChannels();
        }

        //设置开始处理事件标志为true
        eventHandling_ = true;

        for(auto iter : activeChannels_)
        {
            currentChannel = iter;

            //处理事件
            currentChannel->handleEvent(pollReturnTime_);
        }
        currentChannel = NULL;

        //设置开始处理事件标志为false 事件处理结束
        eventHandling_ = false;
        //开始执行投递函数对列中的回调函数
        doPendingFunctors();

    }
    //loop结束
    LOG_TRACE << "EventLoop " << this << " stop looping";
    looping_ = false;
}

//让reactor退出循环
//因为调用quit的线程和执行reactor的线程不一定相同，如果他们不是同一个线程
//那么必须使用wakeup函数让wakeupChannel被激活　然后轮询函数返回，就可以处理事件　然后进入下一个循环
//就能知道quit_已经被设置为true　从而退出循环
void EventLoop::quit()
{
    quit_ = true;
    if(!isInLoopThread())
    {
        wakeup();
    }
}

//运行一个回调函数　或者　把回调函数投递到队列中等待io线程处理
void EventLoop::runInLoop(const Functor &&cb)
{
    if(isInLoopThread())
    {
        cb();
    } else
    {
        //如果不在同一个线程　那么把他添加到投递回调函数队列中
        queueInLoop(std::move(cb));
    }
}

//把一个回调函数添加到投递回调函数队列中，并唤醒reactor
void EventLoop::queueInLoop(const Functor &&cb)
{
    //因为投递函数队列可能有多个线程访问　因此要加锁保护
    Mu::Base::MutexLockGuard lock(mutex_);
    pendingFunctors_.push_back(std::move(cb));
    //如果不是当前线程调用，或者正在执行pendingFunctors_中的任务，都要唤醒EventLoop的owner线程，
    //让其执行pendingFunctors_中的任务。如果正在执行pendingFunctors_中的任务，
    //添加新任务后不会执行新的任务，因为functors.swap(pendingFunctors_)后，
    //执行的是functors中的任务。
    if(!isInLoopThread() || callingPendingFunctors_)
    {
        wakeup();
    }
}

//添加定时器函数：在某个时间点执行
TimerId EventLoop::runAt(const Mu::Base::Timestamp &time, const TimerCallback &&cb)
{
    return TimerQueue->addTimer(std::move(cb), time, 0, 0);
}

//添加定时器：在delay秒后执行
TimerId EventLoop::runAfter(double delay, const TimerCallback &&cb)
{
    Mu::Base::Timestamp time(Mu::Base::addTime(Mu::Base::Timestamp::now(), delay));
    return runAt(time, std::move(cb));
}

//添加定时器：每隔interval秒执行一次
TimeId EventLoop::runEvery(double interval, const TimerCallback &&cb)
{
    Mu::Base::Timestamp time(Mu::Base::addTime(Mu::Base::Timestamp::now(), interval));
    return TimerQueue->addTimer(std::move(cb), time, interval);
}

//取消一个定时器
void EventLoop::cancel(TimeId timeId)
{
    return TimerQueue->cancel(timeId);
}

//fixme:一点想法　稍后验证
//TcpConnection是拥有一个Channel的，它负责管理该Channel的生命周期，
//但是却必须把Channel的裸指针暴露给EventLoop（确切的讲是暴露给Poller），因为Poller需要对Channel的事件进行管理（添加、修改、删除）。
//poller的生命期由EventLoop管理　poller有一个文件描述符到事件处理器的映射表
//每次poller->poll就从这个表中返回活动的事件处理器　当removeChannel时
//实际删除的是poller中的channel　而Eventloop中的channel不删除也可以
//因为POLLER只会从映射表中选取活动的channel fillActiveChannel
//EventLoop::removeChannel表示不关注这个channel了

//更新事件处理器
void EventLoop::updateChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    //只能在io线程调用这个函数
    assertInLoopThread();
    //poller执行更新事件处理器的操作
    poller_->updateChannel(channel);
}

//移除一个事件处理器
void EventLoop::removeChannel(Channel *channel)
{
    //断言channel是否归属于这个EventLoop
    assert(channel->ownerLoop() == this);
    //只能在io线程调用
    assertInLoopThread();
    //如果正在执行事件处理
    if(eventHandling_)
    {//断言这个channel就是正在执行事件处理的事件处理器　或者　被移除的channel没有数据到达
        assert(currentChannel == channel ||
                std::find(activeChannels_.begin(), activeChannels_.end(), channel) == activeChannels_.end());
    }
    //poller执行删除事件处理器的操作
    poller_->removeChannel();
}

//判断轮询器是否有事件处理器
bool EventLoop::hasChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    return poller_->hasChannel(channel);
}

//退出进程
void EventLoop::abortNotInLoopThread()
{
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
              << this << " was created in threadId_ " << threadId_ <<
              "Current Thread id = " << Mu::Base::CurrentThread::tid();
}

//唤醒　其实就是告诉reactor循环有某件事情发生了　让它唤醒去及时处理
void EventLoop::wakeup()
{
    uint64_t one  = 1;
    //向线程写８个字节数据
    ssize_t n = Mu::Net::sockets::write(wakeupFd_, &one, sizeof(one));
    if(n != sizeof(one))
    {
        LOG_ERROR << "EventLoop::wakeup() write " << n << " bytes instead of 8";
    }
}

//被waitupChannel调用
//waitupChannel因为waitup()发送了数据给他所以有数据可读
//而waitupChannel的handleEvent会调用读的回调函数　waitupChannel的回调函数就是EventLoop::handleRead
//EventLoop::handleRead什么也不做　只是读取那八字节字符
void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t  n = Mu::Net::sockets::read(wakeupFd_, &one, sizeof(one));
    if(n != sizeof(one))
    {
        LOG_ERROR << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
    }
}

//执行投递的回调函数
void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;
    {
        //先用锁锁住队列　因为队列可能有多个线程访问
        Mu::Base::MutexLockGuard lock(mutex_);
        //交换的目的是为了让pendingFunctors继续存放投递的回调函数
        //避免由于执行回调函数的时间过长导致锁住pendingFunctors的时间过长
        //从而导致pendingFunctor不能存放新投递的回调函数
        //通过交换　可以使functors专门用于执行投递的回调函数
        functors.swap(pendingFunctors_);
    }

    for(size_t i = 0; i < functors.size(); i ++)
    {
        functors[i]();
    }
    callingPendingFunctors_ = false;

}

//打印已经激活的事件处理器
void EventLoop::printActiveChannels() const
{
    for(auto channel : activeChannels_)
    {
        Channel *ch = channel;
        LOG_TRACE << "{" << ch->reventToString() << "}";
    }
}
//
// Created by jackson on 17-3-11.
//

#ifndef SIMPLENETWORDLIBRARY_EVENTLOOP_H
#define SIMPLENETWORDLIBRARY_EVENTLOOP_H

#include <functional>
#include <memory>
#include <vector>
#include "../Base/TimeStamp.h"
#include "../Base/Mutex.h"

namespace Mu
{
namespace Net
{
    class Channel;
    class Poller;
    class TimerQueue;
    //事件循环　即Reactor 一个线程最多有一个EventLoop
    //创建并运行EventLoop的线程是IO线程
    class EventLoop
    {
    public:
        typedef std::function<void()> Functor;
        //禁止复制
        EventLoop(const EventLoop &) = delete;
        EventLoop& operator=(const EventLoop &) = delete;

        EventLoop();
        ~EventLoop();

        //事件循环，逆序在同一个线程内创建reactor对象和调用它的loop方法
        void loop();
        //退出事件循环
        void quit();

        //轮询返回的时间，通常表示事件到来
        Mu::Base::Timestamp pollReturnTime() const
        {
            return pollReturnTime_;
        }
        //返回迭代器
        int64_t iteration() const
        {
            return iteration_;
        }
        //如果调用runInLoop的线程与EventLoop所在的线程一样
        //就立即调用函数cb　否则　将函数cb放入一个投递函数队列中
        //等待EventLoop所在线程对队列中的函数进行处理
        //这个函数可以让io都在io线程中处理　是线程安全的
        void runInLoop(const Functor &cb);
        //当调用该函数的线程不是io线程时　把回调函数放在一个队列中
        //在轮询之后调用
        void queueInLoop(const Functor &cb);
        //c++11右值
        void runInLoop(const Functor &&cb);
        void queueInLoop(const Functor &&cb);

        //在指定的时间调用回调函数
        TimeId runAt(const Mu::Base::Timestamp &time, const TimerCallback &cb);
        //在delay秒后调用一次回调函数
        TimeId runAfter(double delay, const TimerCallback &cb);
        //每隔interval秒调用一次回调函数
        TimeId runEvery(double interval, const TimerCallback &cb);
        //取消一个定时器
        void cancel(TimeId timeId);

        //c++11右值
        //在指定的时间调用回调函数
        TimeId runAt(const Mu::Base::Timestamp &time, const TimerCallback &&cb);
        //在delay秒后调用一次回调函数
        TimeId runAfter(double delay, const TimerCallback &&cb);
        //每隔interval秒调用一次回调函数
        TimeId runEvery(double interval, const TimerCallback &&cb);
        //取消一个定时器
        void cancel(TimeId timeId);

        //下面的函数供内部使用

        //向一个文件描述符写入一字节数据　唤醒reactor
        void wakeup();

        //更新事件处理器
        void updateChannel(Channel *channel);
        //移除事件处理器
        void removeChannel(Channel *channel);

        //是否有某一个事件处理器
        bool hasChannel(Channel *channel);

        //断言自己是否在io线程中　如果不在　则退出程序
        void assertInLoopThread()
        {
            if(!isInLoopThread())
            {
                abortNotInLoopThread();
            }
        }

        //是否在io队列中
        bool isInLoopThread() const
        {
            return (threadId_ == Mu::Base::CurrentThread::tid());
        }
        //是否正在处理事件
        bool eventHandling() const
        {
            return eventHandling_;
        }

        //设置上下文
        void setContext(const auto &context)
        {
            context_ = context;
        }
        //返回上下文
        const auto &getContext() const
        {
            return context_;
        }
        //返回可修改的上下文
        auto *getContext()
        {
            return &context_;
        }

        //返回当前线程的reactor对象
        static EventLoop * getEventLoopOfCurrentThread();
    private:

        //如果创建的EventLoop的线程和运行EventLoop的线程不是同一个线程　则退出程序
        void abortNotInLoopThread();

        //处理可读事件(wake up)
        void handleRead();

        //执行投递到队列中的回调函数
        void doPendingFunctors();

        //用于DEBUG
        void printActiveChannels() const;

        typedef std::vector<Channel *> ChannelList;

        //是否在循环中
        bool looping_;
        //是否退出循环
        bool quit_;

        //是否正在处理事件
        bool eventHandling_;
        //是否正在执行投递的函数
        bool callingPendingFunctors_;

        //迭代器
        int64_t iteration_;

        //线程id
        pid_t threadId_;


        //用于唤醒的描述符（将Reactor从沉睡中唤醒
        int wakeupFd_;
        //唤醒事件的处理器（不暴露给用户）
        std::unique_ptr<Channel> wakeupChannel_;

        //轮询返回的时间
        Mu::Base::Timestamp pollReturnTime_;
        //轮询器
        std::unique_ptr<Poller> poller_;

        //定时器队列
        std::unique_ptr<TimerQueue> timerQueue_;

        //上下文
        auto context_;

        //已经激活的事件处理器队列
        ChannelList activeChannels_;
        //当前正在调用的事件处理器
        Channel *currentChannel;

        //互斥锁　用来锁住回调函数队列
        Mu::Base::MutexLock mutex_;
        //投递的回调函数队列
        std::vector<Functor> pendingFunctors_;

    };
}
}


#endif //SIMPLENETWORDLIBRARY_EVENTLOOP_H

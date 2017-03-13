//
// Created by jackson on 17-3-12.
//

#ifndef SIMPLENETWORDLIBRARY_TIMERQUEUE_H
#define SIMPLENETWORDLIBRARY_TIMERQUEUE_H

#include <set>
#include "../Base/TimeStamp.h"
#include "Channel.h"
#include "TimerId.h"

namespace Mu
{
namespace Net
{
    class Timer;
    class EventLoop;
    typedef Mu::Base::Timestamp Timestamp;
    //定时器队列
    class TimerQueue
    {
    public:
        typedef std::function<void()> TimerCallback;
        //禁止复制
        TimerQueue(const TimerQueue &) = delete;
        TimerQueue& operator=(const TimerQueue &) = delete;

        //构造函数
        TimerQueue(EventLoop *loop);
        ~TimerQueue();

        //添加一个定时器
        //必须是线程安全的　因为一般从其他线程调用
        //所以会调用addTimerInQueue函数将添加定时器的任务转移到io线程
        //下面的cancel函数也一样
        TimerId addTimer(const TimerCallback &&cb, Timestamp when. double interval);

        //取消一个定时器　必须是线程安全的
        void cancel(TimerId timerId);

    private:
        //把添加一个定时器的任务转移到io线程
        void addTimerInLoop(Timer *timer);
        //把删除一个定时器的任务转移到io线程
        void cancelTimerInLoop(TimerId timerId);

        //系统定时器到期(表示定时器队列中超时时间最早的定时器已经超时)
        //处理timerfd到期事件
        void handleRead();

        //计时器列表中的元素实体
        typedef std::pair<Timestamp, Timer *> Entry;
        //计时器列表　用set存储　set可以自动按timestamp升序排列
        typedef std::set<Entry> TimerList;
        //活动的计时器
        typedef std::pair<Timer *, int64_t > ActiveTimer;
        //活动计时器的集合
        typedef std::set<ActiveTimer> ActiveTimerList;

        //获取所有已经超时的定时器，并慈宁宫定时器队列和活动定时器队列中把它们删除
        std::vector<Entry> getExpired(Timestamp now);

        //重置getExpried中超时被删除的计时器
        //重置周期性的定时器，删除一次性或被取消的计时器
        void reset(const std::vector<Entry> &expried, Timestamp now);

        //插入计时器
        bool insert(Timer *timer);

        //所属的EventLoop
        EventLoop * loop_;
        //定时器文件描述符（reactor用这个文件描述符产生的事件激活定时器事件）
        const int timeFd_;
        //定时器描述符事件处理器
        Channel timeFdChannel_;
        //定时器列表
        TimerList timers_;
        //活动定时器列表
        ActiveTimerList activeTimers_;
        //timers_.size() == activeTimers.size()

        //是否正在处理超时任务
        bool callingExpiredTimers_;
        //被取消的定时器集合
        ActiveTimerList cancelingTimers_;
    };
}
}

#endif //SIMPLENETWORDLIBRARY_TIMERQUEUE_H

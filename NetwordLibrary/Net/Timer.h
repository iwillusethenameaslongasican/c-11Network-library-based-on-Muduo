//
// Created by jackson on 17-3-12.
//

#ifndef SIMPLENETWORDLIBRARY_TIMER_H
#define SIMPLENETWORDLIBRARY_TIMER_H

#include <functional>
#include <atomic>
#include "../Base/TimeStamp.h"

namespace Mu
{
namespace Net
{
    typedef Mu::Base::Timestamp Timestamp;
    //定时器
    //timer类用于一个定时类事件
    class Timer
    {
    public:
        typedef std::function<void ()> TimerCallback;
        //禁止复制
        Timer(const Timer &) = delete;
        Timer& operator=(const Timer &) = delete;

        //构造函数　右值
        Timer(const TimerCallback &&cb, Timestamp time, int interval):
                callback_(std::move(cb)),
                time_(time),
                interval_(interval),
                repeat_(interval ? true : false),
                sequence_(++ s_numCreated_)
        {}
        //运行定时器回调函数s
        void run()
        {
            callback_();
        }
        //获取到期时间
        MTimestamp expiration() const
        {
            return time_;
        }
        //是否是周期性定时器
        bool repeat() const
        {
            return repeat_;
        }
        //获取定时器序号
        int64_t sequence() const
        {
            return sequence_;
        }

        //重新开始
        void restart(Timestamp now);

        static std::atomic_int_least64_t numCreated();


    private:
        //定时器的回调函数
        const TimerCallback callback_;
        //到期时间
        Timestamp time_;
        //周期时间
        const double interval_;
        //是否重复
        const bool repeat_;
        //计时器序号　由s_numCreated_计算出
        static int64_t sequence_;
        //创建了多少个计时器
        static std::atomic_int_least64_t s_numCreated_;

    };
}
}
#endif //SIMPLENETWORDLIBRARY_TIMER_H

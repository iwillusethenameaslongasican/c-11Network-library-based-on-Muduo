//
// Created by jackson on 17-3-12.
//

#ifndef SIMPLENETWORDLIBRARY_TIMERID_H
#define SIMPLENETWORDLIBRARY_TIMERID_H

#include <cstdint>
#include <clocale>

namespace Mu
{
namespace Net
{
    class Timer;
    //定时器id类
    //被TimerQueue类使用　主要作用是用于撤销定时器
    //TimerQueue使用TimerId的sequence_或timer_来标识一个计时器
    class TimerId
    {
    public:
        //这个类可以复制
        //默认构造函数
        TimerId():
                timer_(NULL),
                sequence_(0)
        {}
        TimerId(Timer *timer, int64_t sequece)
                : timer_(timer),
                  sequence_(sequece)
        {}

        //设置TimerQueue为友元类　让TimerQueue可以访问TimerId的私有成员
        friend class TimerQueue;

    private:
        //所属定时器
        Timer *timer_;
        //序号
        int64_t sequence_;
    };
}
}

#endif //SIMPLENETWORDLIBRARY_TIMERID_H

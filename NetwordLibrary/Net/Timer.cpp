//
// Created by jackson on 17-3-12.
//

#include "Timer.h"

using namespace Mu;
using namespace Net;

std::atomic_int_least64_t s_numCreated_;
//重新设置到期时间
void Timer::restart(Timestamp now)
{
    //如果是周期定时器
    if(repeat_)
    {
        //重新设置到期时间为从现在开始interval秒后
        time_ = Mu::Base::addTime(now, interval_);
    }
    else//如果不是周期性函数　则把到期时间赋值为无意义的时间
    {
        time_ = Timestamp::invalid();
    }

}
//
// Created by jackson on 17-3-5.
//

#include "Condition.h"
#include <errno.h>

using namespace Mu;
using namespace Base;

bool Condition::waitForSeconds(int seconds)
{
    struct timespec abstime;
//    CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,
// 即从UTC1970-1-1 0:0:0开始计时,中间时刻如果系统时间被用户该成其他,
// 则对应的时间相应改变
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += seconds;
    return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getMutex(), &abstime);

}


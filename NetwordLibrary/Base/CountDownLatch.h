//
// Created by jackson on 17-3-5.
//

#ifndef SIMPLENETWORDLIBRARY_COUNTDOWNLATCH_H
#define SIMPLENETWORDLIBRARY_COUNTDOWNLATCH_H

#include "Condition.h"
#include "Mutex.h"

namespace Mu
{
namespace Base
{   //封装条件变量的计时器
    class CountDownLatch
    {
    public:
        CountDownLatch(const CountDownLatch &) = delete;
        CountDownLatch& operator=(const CountDownLatch &) = delete;
        //构造函数　显式调用
        CountDownLatch(int count): mutex_(), condition_(mutex_), count_(count){}
        //等待函数
        void wait();
        //计数减１
        void countDown();
        //获取当前计数器的值
        int getCount() const;
    private:
        //CountDownLatch持有锁和条件变量
        //mutable表明在const里可以改变他的状态
        mutable MutexLock mutex_;
        Condition condition_;
        int count_;//计数器
    };
}
}

#endif //SIMPLENETWORDLIBRARY_COUNTDOWNLATCH_H

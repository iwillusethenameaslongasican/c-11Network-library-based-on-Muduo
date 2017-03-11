//
// Created by jackson on 17-3-5.
//
#include "CountDownLatch.h"

using namespace Mu;
using namespace Base;

void CountDownLatch::wait()
{
    MutexLockGuard lock(mutex_);
    //count不为０则一直等待
    while (count_ > 0)
    {
        condition_.wait();
    }
}

void CountDownLatch::countDown()
{
    MutexLockGuard lock(mutex_);
    count_ --;//减少count的计数值
    //若count为０　，则通知所以等待线程
    if(count_ == 0)
    {
        condition_.notifyAll();
    }

}

int CountDownLatch::getCount() const
{
    MutexLockGuard lock(mutex_);
    return count_;
}

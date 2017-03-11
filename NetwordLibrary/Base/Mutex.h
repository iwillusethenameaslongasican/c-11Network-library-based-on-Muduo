//
// Created by jackson on 17-3-4.
//
#ifndef SIMPLENETWORDLIBRARY_MUTEX_H
#define SIMPLENETWORDLIBRARY_MUTEX_H
#include <zconf.h>
#include <assert.h>
#include <pthread.h>
#include "CurrentThread.h"

namespace Mu
{
namespace Base
{
    //用RAII封装互斥锁
    class MutexLock
    {
    public:
        MutexLock() : owner_(0)
        {
            int result = pthread_mutex_init(&mutex_, NULL);
            assert(result == 0);
        }
        MutexLock(const MutexLock &mutex) = delete;
        ~MutexLock()
        {
            assert(owner_ == 0);
            int result = pthread_mutex_destroy(&mutex_);
            assert(result == 0);
        }

        void lock()
        {
            pthread_mutex_lock(&mutex_);
            owner_ = CurrentThread::tid();
        }
        void unlock()
        {
            owner_ = 0;
            pthread_mutex_unlock(&mutex_);
        }

        pthread_mutex_t * getMutex()
        {
            return &mutex_;
        }

        bool isLockByCurrentThread()
        {
            return owner_ == CurrentThread::tid();
        }
        //断言当前是否在持有锁的线程
        void assertLocked()
        {
            assert (isLockByCurrentThread());
        }

    private:
        pthread_mutex_t mutex_;
        //owner保存持有锁的线程id
        pid_t owner_;
    };

    class MutexLockGuard
    {
    public:
        MutexLockGuard(const MutexLockGuard &mutex) = delete;

        explicit MutexLockGuard(MutexLock &mutex) : mutex_(mutex)
        {
            mutex_.lock();
        }
        ~MutexLockGuard()
        {
            mutex_.unlock();
        }

    private:
        //因为MutexLock是不可复制的，所以这里是引用
        //整个对象结束的时候mutex_并没有结束(引用)
        //因为MutexLockGuard只是对其他对象持有的锁进行加锁解锁操作
        //它不负责销毁其他对象持有的锁
        MutexLock &mutex_;
    };
}
}

#define MutexLockGuard(x) error "Missing guard object name"
#endif //SIMPLENETWORDLIBRARY_MUTEX_H
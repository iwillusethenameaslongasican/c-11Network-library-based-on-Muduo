//
// Created by jackson on 17-3-5.
//

#ifndef SIMPLENETWORDLIBRARY_CONDITION_H
#define SIMPLENETWORDLIBRARY_CONDITION_H

#include "Mutex.h"

namespace Mu {
namespace Base
{
    class Condition
    {
    public:
        Condition(const Condition &) = delete;

        Condition &operator=(const Condition &) = delete;
        //构造函数只能显式调用
        explicit Condition(MutexLock &mutex) : mutex_(mutex)
        {
            //构造函数初始化条件变量
            pthread_cond_init(&pcond_, NULL);
        }

        ~Condition()
        {   //析构函数销毁条件变量
            pthread_cond_destroy(&pcond_);
        }

        //等待函数
        void wait()
        {
            pthread_cond_wait(&pcond_, mutex_.getMutex());
        }

        //signal函数
        void notify()
        {
            pthread_cond_signal(&pcond_);
        }

        //boardcast函数
        void notifyAll()
        {
            pthread_cond_broadcast(&pcond_);
        }
        //返回true如果超时，否则返回false
        bool waitForSeconds(int seconds);


        private:
        MutexLock &mutex_;//锁　，不拥有它，只拥有引用，因为锁是不可复制的
        pthread_cond_t pcond_;//条件变量
    };
}
}
#endif //SIMPLENETWORDLIBRARY_CONDITION_H

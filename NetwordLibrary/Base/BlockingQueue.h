//
// Created by jackson on 17-3-5.
//

#ifndef SIMPLENETWORDLIBRARY_BLOCKINGQUEUE_H
#define SIMPLENETWORDLIBRARY_BLOCKINGQUEUE_H

#include <queue>
#include "Condition.h"

namespace Mu
{
namespace Base
{
     //无界队列,这是一个模板类
    template <typename T>
    class BlockQueue
    {
    public:
        BlockQueue(const BlockQueue &) = delete;
        BlockQueue& operator=(const BlockQueue &) = delete;

        BlockQueue(): mutex_(), condition_(mutex_), queue_(){}
        //生产产品
        void put(const T &&x)//右值
        {
            MutexLockGuard lock(mutex_);
            queue_.push_back(std::move(x));
            condition_.notify();
        }
        //消费产品
        T take()
        {
            MutexLockGuard lock(mutex_);
            //如果队列为空 则一直等待
            while(queue_.empty())
            {
                condition_.wait();
            }
            //再断言一些判断队列是否为空
            assert(!queue_.empty());
            //取出队头元素
            T x(std::move(queue_.front()));//右值
            queue_.pop_front();
            return x;
        }
        //返回队列大小
        ssize_t size() const
        {
            MutexLockGuard lock(mutex_);
            return queue_.size();
        }
    private:
        //mutable使变量在const方法中可以被改变
        mutable MutexLock mutex_;
        //条件变量
        Condition condition_;
        //使用双端队列deque 和vector只能高效地插入和删除尾部元素不同
        //deque还可以高效地插入和删除头部元素
        std::deque<T> queue_;
    };

}
}

#endif //SIMPLENETWORDLIBRARY_BLOCKINGQUEUE_H

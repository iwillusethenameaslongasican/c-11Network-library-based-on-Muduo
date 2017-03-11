//
// Created by jackson on 17-3-6.
//

#ifndef SIMPLENETWORDLIBRARY_BOUNDEDBLOCKINGQUEUE_H
#define SIMPLENETWORDLIBRARY_BOUNDEDBLOCKINGQUEUE_H

#include "Mutex.h"
#include "Condition.h"

#include <deque>

namespace Mu
{
namespace Base
{
    template <typename T>
    class BoundedBlockingQueue
    {
    public:
        //禁止复制
        BoundedBlockingQueue(const BoundedBlockingQueue &) = delete;
        BoundedBlockingQueue& operator=(const BoundedBlockingQueue &) = delete;
        //构造函数 只能显式调用
        explicit BoundedBlockingQueue(int maxQueueSize): mutex_(),
                                                NotEmpty_(mutex_),
                                                NotFull_(mutex_),
                                                queueSize_(maxQueueSize)
        {}

        bool isEmpty() const
        {
            MutexLockGuard lock(mutex_);
            return queue_.empty();
        }

        bool isFull() const
        {
            MutexLockGuard lock(mutex_);
            return queue_.size() == queueSize_;
        }
        //放入物品
        void put(T &&x)
        {
            MutexLockGuard lock(mutex_);
            //如果队列满，则一直等待
            while(queue_.size() == queueSize_)
            {
                NotFull_.wait();
            }
            assert(queue_.size() != queueSize_);
            //放入物品 右值引用
            queue_.push_back(std::move(x));
            //通知消费者队列中有物品了
            NotEmpty_.notify();
        }
        //取出物品 右值引用
        T take()
        {
            MutexLockGuard lock(mutex_);
            //当queue为空时 等待
            while(queue_.empty())
            {
                NotEmpty_.wait();
            }
            assert(!queue_.empty());
            //取出物品 右值引用
            T front(std::move(queue_.front()));
            queue_.pop_front();
            //通知生产者队列不 满
            NotFull_.notify();
            return front;
        }

        //返回队列大小
        ssize_t size() const
        {
            MutexLockGuard lock(mutex_);
            return queue_.size();
        }


    private:
        //mutable 表示在const函数中可以被改变
        mutable MutexLock mutex_;
        //条件变量 队列是否为空
        Condition NotEmpty_;
        //条件变量 队列是否为满
        Condition NotFull_;
        std::deque<T> queue_;
        int queueSize_;
    };
}
}

#endif //SIMPLENETWORDLIBRARY_BOUNDEDBLOCKINGQUEUE_H

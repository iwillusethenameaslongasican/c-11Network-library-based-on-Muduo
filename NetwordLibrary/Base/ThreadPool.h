//
// Created by jackson on 17-3-6.
//

#ifndef SIMPLENETWORDLIBRARY_THREADPOOL_H
#define SIMPLENETWORDLIBRARY_THREADPOOL_H

#include "Mutex.h"
#include "Condition.h"
#include "Thread.h"

#include <deque>
#include <functional>
#include <vector>
#include <memory>

namespace Mu
{
namespace Base
{
    class ThreadPool
    {
        typedef std::function<void ()> Task;
    public:
        //禁止复制
        ThreadPool(const ThreadPool &) = delete;
        ThreadPool& operator=(const ThreadPool &) = delete;

        //构造函数 需要显式调用
        explicit ThreadPool(const std::string& name = std::string());
        //析构函数
        ~ThreadPool();

        //启动线程池
        void start(int numThreads);
        //关闭线程池
        void stop();

        //直接运行任务，或者往线程池当中的任务队列添加任务
        void run(const Task &task);

    private:
        //线程池当中的线程要执行的函数
        void runInThread();
        //获取任务
        Task take();

        //和条件变量配合使用的互斥锁
        mutable MutexLock mutex_;
        //条件变量用来唤醒线程池中的线程队列来执行任务
        Condition condition_;
        //存放任务的任务队列
        std::deque<Task> task_;
        //线程池名字
        std::string name_;
        //存放线程指针的数组
        std::vector<std::shared_ptr<Thread>> threads_;
//        std::vector<Thread *> threads_;
        //线程池是否处于运行状态
        bool running_;
    };
}
}


#endif //SIMPLENETWORDLIBRARY_THREADPOOL_H

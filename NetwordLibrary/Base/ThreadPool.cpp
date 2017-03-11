//
// Created by jackson on 17-3-6.
//

#include "ThreadPool.h"
#include <algorithm>

using namespace Mu;
using namespace Base;

ThreadPool::ThreadPool(const std::string &name):
        mutex_(),
        condition_(mutex_),
        name_(name),
        running_(false)
{

}

ThreadPool::~ThreadPool()
{
    //让线程池停止运行
    if(running_)
    {
        stop();
    }
}
//启动线程池
void ThreadPool::start(int numThreads)
{//不用加锁，因为只在线程池启动的时候调用一次
    //先断言线程池现在为空
    assert(threads_.size() == 0);
    //线程池开始运行
    running_ = true;
    //先给线程池数组预留空间
    threads_.reserve(numThreads);
    //新建线程并绑定线程回调函数,把新建的线程放入线程池数组中
    for(int i = 0; i < numThreads; i ++)
    {
        char id[32];
        //线程id
        snprintf(id, sizeof(id), "%d", i);
        //绑定线程的回调函数为runInThread函数
        threads_.push_back(std::shared_ptr<Thread>(new Thread(std::bind(&ThreadPool::runInThread, this), name_ + id)));
        //启动线程
        threads_[i]->start();
    }
}
//停止线程池
void ThreadPool::stop()
{
    {
        //先加锁，因为可能有多个线程操作线程
        MutexLockGuard lock(mutex_);
        //设置线程池运行标志为false
        running_ = false;
        //通知所有线程
        condition_.notifyAll();
    }
    std::for_each(threads_.begin(), threads_.end(), std::bind(&Thread::join, std::placeholders::_1));
}

//往任务队列添加任务
void ThreadPool::run(const Task &task)
{//将任务添加到线程池当中的任务队列
    //如果线程池为空 直接执行
    if(threads_.empty())
    {
        task();
    }
    else
    {//要加锁
        MutexLockGuard lock(mutex_);
        task_.push_back(task);
        //通知线程进行处理
        condition_.notify();
    }
}
//获取任务
ThreadPool::Task ThreadPool::take()
{
    //先加锁
    MutexLockGuard lock(mutex_);
    //如果队列为空并且线程池还未关闭。则一直等待
    //直到队列不空 或者线程池被关闭
    //要用while 防止虚假唤醒
    while(task_.empty() && running_)
    {
        condition_.wait();
    }
    //新建一个任务 如果队列不空 则它等于队列中的任务函数
    //否则代表线程池即将关闭 任务为空
    Task task;
    if(!task_.empty())
    {
        task = task_.front();//取出任务
        task_.pop_front();//弹出任务
    }
    return task;
}

//运行线程池任务队列中的任务函数
void ThreadPool::runInThread()
{
    try {
        while(running_)
        {
            //获得任务
            Task task = take();
            //如果任务函数不为空
            if(task)
            {
                //执行任务
                task();
            }
        }
    }
//    catch (const Exception& ex)//异常捕获
//    {
//        fprintf(stderr, "exception caught in ThreadPool %s\n", name_.c_str());
//        fprintf(stderr, "reason: %s\n", ex.what());
//        fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
//        abort();
//    }
    catch (const std::exception& ex)
    {
        fprintf(stderr, "exception caught in ThreadPool %s\n", name_.c_str());
        fprintf(stderr, "reason: %s\n", ex.what());
        abort();
    }
    catch (...)
    {
        fprintf(stderr, "unknown exception caught in ThreadPool %s\n", name_.c_str());
        throw; // rethrow
    }

}
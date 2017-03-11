//
// Created by jackson on 17-3-5.
//

#include "BlockingQueue.h"
#include "CountDownLatch.h"
#include "Thread.h"
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using namespace Mu;
using namespace Base;
using namespace std;

class Test
{
public:
    //count为条件变量计时器，numsThread为线程数目
    Test(int count, int numsThread): queue_(),latch_(count)
    {
        threads_.reserve(numsThread);
        for(int i = 0; i < numsThread; i ++)
        {
            //线程名字
            char name[32];
            snprintf(name, sizeof(name), "work thread %d", i);
            //创建numsThread个线程，threadFunc为回调函数
            threads_.push_back(std::move(std::unique_ptr<Thread>(new Thread(std::bind(&Test::threadFunc, this), string(name)))));
        }
        //启动线程
        std::for_each(threads_.begin(), threads_.end(), std::bind(&Thread::start, std::placeholders::_1));
    }

    void run(int times)
    {
        printf("waiting for count down latch\n");
        latch_.wait();
        printf("all threads started\n");
        for(int i = 0; i < times; i ++)
        {
            char buf[32];
            snprintf(buf, sizeof(buf), "hello %d", i);
            queue_.put(std::string(buf));//往队列中添加100个产品
            printf("tid=%d, pid=%d, put date=%s, size=%zd\n", CurrentThread::tid(), ::getpid(), buf, queue_.size());

        }
    }

    void joinAll()
    {
        for(int i = 0; i < threads_.size(); i ++)
        {
            //往队列中加入等于线程数目的stop 线程取出这个stop时会关闭
            queue_.put(string("stop"));
        }
        //执行join
        std::for_each(threads_.begin(), threads_.end(), std::bind(&Thread::join, std::placeholders::_1));
    }

private:
    void threadFunc()
    {
        printf("tid=%d, pid=%d, %s started\n", CurrentThread::tid(), ::getpid(), CurrentThread::tidName());
        //计数值减1
        latch_.countDown();
        bool running = true;
        while(running)
        {
            //消费产品
            std::string product(queue_.take());
            //打印产品信息
            printf("tid=%d, pid=%d, data=%s, size==%zd\n", CurrentThread::tid(), ::getpid(), product.c_str(), queue_.size());
            //直到产品的名称==stop，退出循环
            running = (product != "stop");
        }
        //打印停止消息
        printf("tid=%d, pid=%d, %s stopped\n", CurrentThread::tid(), ::getpid(), CurrentThread::tidName());
    }
    BlockQueue<string> queue_;
    CountDownLatch latch_;
    std::vector<unique_ptr<Thread>> threads_;
};

int main()
{
    //打印进程，线程id
    printf("tid=%d, pid=%d\n", CurrentThread::tid(), ::getpid());
    Test t(5, 5);
    t.run(100);
    t.joinAll();

    printf("number of created threads: %d\n", Thread::numCreated() );
}
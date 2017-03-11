//
// Created by jackson on 17-3-5.
//

#include <algorithm>
#include <memory>
#include "CountDownLatch.h"
#include "Thread.h"

using namespace Mu;
using namespace Base;

class Test
{
public:
    Test(int threadnums): latch_(1)
    {   //CountDownLatch初始化计数为１，threadnums为线程数量
        for(int i = 0; i < threadnums; i ++)
        {
            char name[32];//线程的名字
            snprintf(name, sizeof(name), "work thread %d", i);
            //创建线程　回调函数为threadFunc　名字为name
            threads_.push_back(std::move(std::unique_ptr<Thread>(new Thread(std::bind(&Test::threadFunc, this), std::string(name)))));
        }
        //启动所有线程 std::placeholders::_1为参数 在这里为数组中的线程的指针
        std::for_each(threads_.begin(), threads_.end(), std::bind(&Thread::start, std::placeholders::_1));
    }

    void run()
    {
        //count_初始化为1，只要执行一次countDown就能跳出等待
        latch_.countDown();
    }

    void joinAll()
    {
        std::for_each(threads_.begin(), threads_.end(), std::bind(&Thread::join, std::placeholders::_1));
    }
private:
    void threadFunc()
    {
        latch_.wait();
        printf("tid=%d. %s started\n", CurrentThread::tid(), CurrentThread::tidName());
        printf("tid=%d. %s stopped\n", CurrentThread::tid(), CurrentThread::tidName());
    }

    CountDownLatch latch_;
    //线程指针使用unique_ptr管理 说明是数组独占的
    std::vector<std::unique_ptr<Thread>> threads_;
};

int main()
{
    //首先打印当前进程pid， 当前线程tid
    printf("pid=%d, tid=%d\n", ::getpid(), CurrentThread::tid());
    //构造Test对象
    Test t(4);
    sleep(3);
    printf("pid=%d, tid=%d, running ...\n", ::getpid(), CurrentThread::tid());
    t.run();
    t.joinAll();
    printf("number of created threads %d\n", Thread::numCreated());
}
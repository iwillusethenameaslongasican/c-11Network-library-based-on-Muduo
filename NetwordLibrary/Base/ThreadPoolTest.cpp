//
// Created by jackson on 17-3-6.
//

#include "ThreadPool.h"
#include "CountDownLatch.h"

using namespace Mu;
using namespace Base;


void print()
{//简单地打印tid
    printf("tid=%d\n", CurrentThread::tid());
}

void printString(const std::string &msg)
{
    printf("tid=%d, data=%s\n", CurrentThread::tid(), msg.c_str());
}

int main()
{
    ThreadPool threadPool("pool");
    //创建有8个线程的线程池
    threadPool.start(50);
    //先往任务队列中添加两个print任务
    threadPool.run(print);
    threadPool.run(print);
    //往线程中添加100个printString任务
    for(int i = 0; i < 1000; i ++)
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "taskID%d", i);
        threadPool.run(std::bind(&printString, std::string(buf)));
    }
    //新建一个1s的计时器
    CountDownLatch latch(1);
    //添加一个任务
    threadPool.run(std::bind(&CountDownLatch::countDown, &latch));
    //count不为0则一直等待
    latch.wait();
    //关闭线程池
    threadPool.stop();
}
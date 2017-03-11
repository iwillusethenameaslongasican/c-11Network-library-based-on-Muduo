//
// Created by jackson on 17-3-4.
//

#include <zconf.h>
#include "Thread.h"
#include "CurrentThread.h"

using namespace std;

void threadFunc()
{
    printf("tid=%d\n", Mu::Base::CurrentThread::tid());
}

void threadFunc2(int x)
{
    printf("tid=%d, x=%d\n", Mu::Base::CurrentThread::tid(), x);
}

class Foo
{
public:
    explicit Foo(double x): x_(x)
    {}

    void memberFunc()
    {
        printf("tid=%d, Foo:x_=%f\n", Mu::Base::CurrentThread::tid(), x_);
    }

    void memberFunc2(const string &str)
    {
        printf("tid=%d, Foo:x_=%f, text=%s\n", Mu::Base::CurrentThread::tid(), x_, str.c_str());
    }

private:
    double x_;
};

int main()
{
    //获取当前线程的pid（进程id）
    printf("pid=%d, tid=%d\n", ::getpid(), Mu::Base::CurrentThread::tid());
    //创建一个线程对象，传递一个函数
    Mu::Base::Thread t1(threadFunc);
    t1.start();
    t1.join();
    //threadFunc2带了一个参数
    Mu::Base::Thread t2(bind(threadFunc2, 42));
    t2.start();
    t2.join();
    //创建一个对象
    Foo foo(88.88);
    //成员函数一定要用&
    Mu::Base::Thread t3(bind(&Foo::memberFunc, &foo));
    t3.start();
    t3.join();
    Mu::Base::Thread t4(bind(&Foo::memberFunc2, ref(foo), string("hanyan")));
    t4.start();
    t4.join();
    //打印最后创建的线程总数
    printf("number of created threads %d\n", Mu::Base::Thread::numCreated());
}
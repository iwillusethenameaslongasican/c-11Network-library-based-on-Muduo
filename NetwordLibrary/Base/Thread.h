//
// Created by jackson on 17-3-4.
//

#ifndef SIMPLENETWORDLIBRARY_THREAD_H
#define SIMPLENETWORDLIBRARY_THREAD_H

#include <functional>
#include <atomic>

namespace Mu
{
namespace Base
{
    class Thread
    {
        typedef std::function<void ()> ThreadFunc;
    public:
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread &) = delete;

        explicit Thread(const ThreadFunc&, const std::string &name = std::string());
        ~Thread();

        pid_t pid() const
        {
            return pid_;
        }
        bool isStart() const
        {
            return start_;
        }
        static int numCreated()
        {
            return numCreated_;
        }
        const std::string & name() const
        {
            return name_;
        }
        //创建线程，调用startThread线程入口函数
        void start();
        int join(); //return pthread_join()


    private:
        //线程入口函数
        static void* startThread(void *thread);
        void runInThread();
//        Linux中，每个进程有一个pid，类型pid_t，由getpid()取得。
//        Linux下的POSIX线程也有一个id，类型 pthread_t，由pthread_self()取得，该id由线程库维护，其id空间是各个进程独立的（即不同进程中的线程可能有相同的id）。
//        Linux中的POSIX线程库实现的线程其实也是一个进程（LWP），只是该进程与主进程（启动线程的进程）共享一些资源而已，比如代码段，数据段等。
//
//        linux多线程环境下gettid() pthread_self() 两个函数都获得线程ID,可它们的返回值不一样。
//        linux使用进程模拟线程，gettid 函数返回实际的进程ID（内核中的线程的ID）.
//        pthread_self 函数返回 pthread_create创建线程时的ID（POSIX thread ID）.
//        有时候我们可能需要知道线程的真实pid。比如进程P1要向另外一个进程P2中的某个线程发送信号时，既不能使用P2的pid，更不能使用线程的pthread id，而只能使用该线程的真实pid，称为tid
        pid_t pid_;
        pthread_t threadId_;
        bool start_;
        ThreadFunc func_;
        std::string name_;
        //原子计数，不同线程对它进行操作的时候会自动对它加锁，相当于每个时刻只有一个线程在操作它
        static std::atomic_int numCreated_;

    };
}
}

#endif //SIMPLENETWORDLIBRARY_THREAD_H

//
// Created by jackson on 17-3-4.
//

#include <zconf.h>
#include <syscall.h>
#include <assert.h>
#include "Thread.h"
#include "CurrentThread.h"

namespace Mu {
    namespace Base {
        namespace CurrentThread {
            //__thread为每个线程独有的变量，下面的变量每个线程一份
            __thread int t_cachedTid = 0;//保存线程真实的tid_t，由于每次返回tid_t都要进行系统调用，因此把它缓存起来
            __thread char t_tidString[32];//tid的字符串形式
            __thread const char *t_threadName = "UNKNOWN";//线程的名字
            const bool sameType = std::is_integral<pid_t>::value;//如果是pid_t时int类型，返回true
            static_assert(sameType, "pid_t and int are not same type");//c++11的断言

        }

        namespace detail {
            pid_t gettid()//通过系统调用获得线程的tid
            {
                return static_cast<pid_t>(::syscall(SYS_gettid));//转换成pid_t类型
            }
// 当一个进程调用了fork之后，子进程需要调用这个函数
            void afterFork()//子进程调用
            {
                Mu::Base::CurrentThread::t_cachedTid = 0;//当前线程的tid为０
                // 当前线程是主线程
                Mu::Base::CurrentThread::t_threadName = "main";//当前线程的名字为main
                Mu::Base::CurrentThread::tid();//缓存线程的tid
            }

        //线程初始化类，在主线程中使用，在创建任何线程之前使用
            class ThreadNameInitailizer {
            public:
                ThreadNameInitailizer() {
                    Mu::Base::CurrentThread::t_threadName = "main";
                    Mu::Base::CurrentThread::tid();//缓存当前线程的pid
                    //#include <pthread.h>
                    //int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));
                    //调用fork时，内部创建子进程前在父进程中会调用prepare，
                    //内部创建子进程成功后，父进程会调用parent ，子进程会调用child
                    pthread_atfork(NULL, NULL, &afterFork);//如果使用fork函数，那么子进程会调用邋afterFork
                }
            };

            ThreadNameInitailizer init;
        }

        using namespace Mu;
        using namespace Base;

        void CurrentThread::cacheTid() {
            if (t_cachedTid == 0) {
                t_cachedTid = detail::gettid();//获得线程的tid
                int n = snprintf(t_tidString, sizeof(t_tidString), "%5d ", t_cachedTid);//将线程的tid存到字符串中
                assert(n == 6);//%5d后面还有一个空格　所以是６
                (void) n;//这一句主要是预防n没有被使用而发生警告
            }
        }

        //判断tid是否等于当前的进程id
        bool CurrentThread::isMainThread() {
            return tid() == ::getpid();
        }

        //静态函数需要在类外定义
        std::atomic_int Thread::numCreated_(0);

        //构造函数　初始化
        Thread::Thread(const ThreadFunc &threadFunc, const std::string &name) :
                pid_(0), threadId_(0),
                start_(false),
                func_(threadFunc),
                name_(name) {
            numCreated_ += 1;
        }

        Thread::~Thread() {}

        void Thread::start() {
            assert(!start_);
            start_ = true;
            //创建线程，startThread为线程的入口
            errno = pthread_create(&threadId_, NULL, &startThread, this);
            if (errno != 0) {//日志
                //LOG_SYSFATAL << "Faile in Pthread_create()";
            }
        }

        int Thread::join() {
            assert(start_);
            return pthread_join(threadId_, NULL);
        }

        //线程入口　参数为该函数的Thread
        void *Thread::startThread(void *obj) {//this指针传到obj
            Thread *thread = static_cast<Thread *>(obj);
            thread->runInThread();//调用线程函数runInThread
            return NULL;
        }

        void Thread::runInThread() {
            pid_ = CurrentThread::tid(); //取得线程的tid
            CurrentThread::t_threadName = name_.c_str();

            try {
                func_();
                CurrentThread::t_threadName = "finished";
            }
//            catch (const Exception& ex)//异常捕捉
//            {
//                Mu::Base::CurrentThread::t_threadName = "crashed";
//                fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
//                fprintf(stderr, "reason: %s\n", ex.what());
//                fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
//                abort();
//            }
            catch (const std::exception &ex) {
                Mu::Base::CurrentThread::t_threadName = "crashed";
                fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
                fprintf(stderr, "reason: %s\n", ex.what());
                abort();
            }
            catch (...) {
                Mu::Base::CurrentThread::t_threadName = "crashed";
                fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
                throw; // rethrow

            }
        }
    }
}
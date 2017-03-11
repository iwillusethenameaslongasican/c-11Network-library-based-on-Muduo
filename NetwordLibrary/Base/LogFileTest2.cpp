//
// Created by jackson on 17-3-9.
//

#include "Logger.h"
#include "LogFile.h"
#include "ThreadPool.h"

#include <stdio.h>

int g_total;
FILE* g_file;//文件指针
std::unique_ptr<Mu::Base::LogFile> g_logFile;//智能指针

void dummyOutput(const char* msg, int len)
{
    g_total += len;//更新g_total
    if (g_file)//最开始g_file，g_logFile都是空的，不执行
    {
        fwrite(msg, 1, len, g_file);
    }
    else if (g_logFile)
    {
        g_logFile->append(msg, len);
    }
}

void bench(const char* type)
{
    Mu::Base::Logger::setOutputFunc(dummyOutput);//更改默认输出
    Mu::Base::Timestamp start(Mu::Base::Timestamp::now());//开始时间
    g_total = 0;

    int n = 1000*1000;//100w次
    const bool kLongLog = false;
    std::string empty = " ";
    std::string longStr(3000, 'X');//3000个X
    longStr += " ";
    for (int i = 0; i < n; ++i)
    {
        LOG_INFO << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz"
                 << (kLongLog ? longStr : empty)//kLongLog真，输出longStr，假输出empty
                 << i;
    }
    Mu::Base::Timestamp end(Mu::Base::Timestamp::now());//截止时间
    double seconds = timeDifferent(end, start);//计算时间差
    //打印到标准输出
    printf("%12s: %f seconds, %d bytes, %10.2f msg/s, %.2f MiB/s\n",
           type, seconds, g_total, n / seconds, g_total / seconds / (1024 * 1024));
}

void logInThread()
{//线程池当中的线程，更新日志
    LOG_INFO << "logInThread";
    usleep(1000);
}

int main()
{//获取父进程pid
    getppid(); // for ltrace and strace
    //建立线程池
    Mu::Base::ThreadPool pool("pool");
    //线程池启动5个线程
    pool.start(5);
    //线程池添加5个任务
    pool.run(logInThread);
    pool.run(logInThread);
    pool.run(logInThread);
    pool.run(logInThread);
    pool.run(logInThread);
    //主线程输出日志
    LOG_TRACE << "trace";
    LOG_DEBUG << "debug";
    LOG_INFO << "Hello";
    LOG_WARN << "World";
    LOG_ERROR << "Error";
    LOG_INFO << sizeof(Mu::Base::Logger);
    LOG_INFO << sizeof(Mu::Base::LogStream);
    LOG_INFO << sizeof(Mu::Base::Fmt);
    LOG_INFO << sizeof(Mu::Base::LogStream::Buffer);
    //睡眠1秒钟
    sleep(1);
    //性能测试程序
    bench("nop");

    char buffer[64*1024];
    //空文件，测试数据写入到/dev/null中的性能
    g_file = fopen("/dev/null", "w");
    setbuffer(g_file, buffer, sizeof buffer);
    bench("/dev/null");
    fclose(g_file);
    //测试数据写入到/tmp/log中的性能
    g_file = fopen("/tmp/log", "w");
    setbuffer(g_file, buffer, sizeof buffer);
    bench("/tmp/log");
    fclose(g_file);

    g_file = NULL;
    //不是线程安全的
    g_logFile.reset(new Mu::Base::LogFile("test_log_st", 500*1000*1000, false));
    bench("test_log_st");

    //线程安全的
    g_logFile.reset(new Mu::Base::LogFile("test_log_mt", 500*1000*1000, true));
    bench("test_log_mt");
    g_logFile.reset();
}
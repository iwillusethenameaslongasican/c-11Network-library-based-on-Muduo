//
// Created by jackson on 17-3-9.
//

#include "Logger.h"
#include "LogFile.h"
#include <memory>
#include <iostream>

using namespace Mu;
using namespace Base;

std::unique_ptr<LogFile> g_logfile;

void outputFunc(const char *msg, int len)
{
    g_logfile->append(msg, len);
}

void flushFunc()
{
    g_logfile->flush();
}


int main()
{


    g_logfile.reset(new LogFile(std::string("log2"), 200 * 1000));
    Logger::setOutputFunc(outputFunc);
    Logger::setFlushFunc(flushFunc);

    std::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for(int i = 0; i < 10000; i ++)
    {
        LOG_TRACE << line;
        //先挂起进程1s 不然写入的速度快过检测是否超过行数的速度 就会造成单个日志文件的大小过大
        usleep(1000);
    }
}
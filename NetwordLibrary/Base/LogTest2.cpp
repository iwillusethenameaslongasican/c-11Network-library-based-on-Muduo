//
// Created by jackson on 17-3-9.
//

#include "Logger.h"
#include <errno.h>
#include <stdio.h>
#include <zconf.h>
#include <iostream>

using namespace Mu;
using namespace Base;

FILE *g_file;

void dummyOutput(const char *msg, int len)
{
    if(g_file)
    {
        fwrite(msg, 1, len, g_file);
    }
}

void dummyFlush()
{
    fflush(g_file);
}

int main()
{
    g_file = ::fopen("/home/c++code/NetwordLibrary/log1", "a");
    if(!g_file)
    {
        std::cout << "failed to open file";
    }
    Logger::setOutputFunc(dummyOutput);
    Logger::setFlushFunc(dummyFlush);

    LOG_TRACE << "TRACE...";
    LOG_DEBUG << "DEBUG...";
    LOG_WARN << "WARN...";
    LOG_INFO << "INFO...";
    LOG_ERROR << "ERROR...";
    LOG_FATAL << "FATAL...";
    errno = 13;
    LOG_SYSERR << "SYSERR...";
   // LOG_SYSFATAL << "SYSFATAL...";

    ::fclose(g_file);
}
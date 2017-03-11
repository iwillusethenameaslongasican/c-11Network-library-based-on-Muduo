//
// Created by jackson on 17-3-9.
//

#include "Logger.h"
#include <errno.h>
using namespace Mu;
using namespace Base;

int main()
{
    LOG_TRACE << "trace...";
    LOG_DEBUG << "debug...";
    LOG_INFO << "info...";
    LOG_WARN << "warn...";
    LOG_ERROR << "error...";
   // LOG_FATAL << "fatal...";
    errno = 13;
    LOG_SYSERR << "syserr...";
   // LOG_SYSFATAL << "sysfatal...";
}
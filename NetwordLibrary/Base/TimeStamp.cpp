//
// Created by jackson on 17-3-4.
//
#include "TimeStamp.h"
#define _STDC_FORMAT_MACROS
#include <inttypes.h>//PRId64所在的头文件，在C++当中需要定义上面那个宏才可以使用PRId64
#include <sys/time.h>

#undef _STDC_FORMAT_MACROS

using namespace Mu;
using namespace Base;

std::string Timestamp::toString() const
{
    char buf[32] = {0};
    int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;//获得秒数
    int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;//获得微秒数
    //PRId64是为了实现跨平台，32位机器表示64位是lld，64位机器表示64位是ld
    snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
    return buf;
}

std::string Timestamp::toFormattedString() const
{
    char buf[32] = {0};
    //得到1970年至今的秒数
    time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
    //得到1970年至今的微秒数
    int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
    struct tm tm_time;
    gmtime_r(&seconds, &tm_time);//gmtime_r将一个秒数转换成一个结构体
    //将结构体里面的时间取出来放进buf里面
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d：%02d:%02d.%06d", tm_time.tm_year + 1900,
    tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, microseconds);
    return buf;

}

//获取当前时间
Timestamp Timestamp::now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);//第二个参数为时区，我们使用默认
    int64_t seconds = tv.tv_sec;
    //得到距离１９７０年微秒数的一个新的时间戳
    return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}

//获取一个失效的时间戳
Timestamp Timestamp::invalid()
{
    return Timestamp();
}
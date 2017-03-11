//
// Created by jackson on 17-3-9.
//


#include "LogFile.h"
#include "FileUtil.h"

namespace Mu
{
namespace Base
{
    LogFile::LogFile(const std::string &basename, int rollsize, int flushInterval, int checkEveryN, bool threadSafe)
        : basename_(basename),
          rollSize_(rollsize),
          flushInterval_(flushInterval),
          checkEveryN_(checkEveryN),
          count_(0),
          mutex_(threadSafe ? (new MutexLock) : NULL),//如果不是线程安全则不用初始化锁
          startOfPeriod_(0),
          lastRoll_(0),
          lastFlush_(0)
    {
        assert(basename.find('/') == std::string::npos);//断言basename不含'/'
        rollFile();//滚动日志
    }

    LogFile::~LogFile() {}

    void LogFile::append(const char *lineMsg, int len)
    {
        if(mutex_)
        {
            MutexLockGuard lock(*mutex_);
            append_unlocked(lineMsg, len);
        }
        else
        {
            append_unlocked(lineMsg, len);
        }
    }

    void LogFile::flush()
    {
        if(mutex_)
        {
            MutexLockGuard lock(*mutex_);
            file_->flush();
        }
        else
        {
            file_->flush();
        }
    }

    bool LogFile::rollFile()
    {
        time_t now = 0;
        std::string filename = getLogFileName(basename_, &now);//取得新的日志文件名
        //先除kPollPerSecondes_再乘kPollPerSeconds表示对齐值值kPollPerSeconds的整数倍，也就是时间会调整到当天的凌晨
        //因为除法会引发向下取整
        time_t start = now / kRollPerSecondes_ * kRollPerSecondes_;
        //如果当前时间大于上次滚动日志的时间（我觉得这一句没什么用，只要不是在很短时间内连续发生两次调用这个函数 应该都能满足这个条件
        //可能是为了处理既写满日志又过了一天两种情况同时发生的情况 这种情况下为了不生成一个几乎为空的日志文件 就加了这一句判断
        if(now > lastRoll_)
        {   //更新最后一次滚动日志时间和刷新时间为现在的系统时间
            lastRoll_ = now;
            lastFlush_ = now;
            //更新日志的当天时间（一定时某一天的凌晨0:0:0）
            startOfPeriod_ = start;
            file_.reset(new FileUtil::AppendFile(filename));//更新只能指针指向的文件
            return true;
        }
        return false;
    }

    void LogFile::append_unlocked(const char *lineMsg, int len)
    {
        file_->append(lineMsg, len);//调用AppendFile的append方法 用不加锁的方式将一行数据写入缓冲区
        //如果缓冲区已写入的数据已经达到要滚动日志的大小，就滚动日志
        if(file_->writtenBytes() > rollSize_)
        {
            rollFile();
        }
        else
        {
            ++ count_;//写入了一行数据 因此日志文件的行数加1
            if(count_ >= checkEveryN_)//每新写入checkEveryN_行检测是否现在的时间是否是新的一天 如果是 则滚动日志
            {
                count_ = 0;//重新计算count_
//              time是这样声明的：
//              time_t time( time_t *timer );
//              用法是先自己定义一个time_t变量，让后把变量的地址传给它。函数会返回自1970年1月1日0点走过的秒数，
//              同时把这个返回值保存在你传进来的那个time_t*指向的变量里面。如果你传进来NULL的话，就不保存。
                time_t now = ::time(NULL);//取得当前系统时间
                //先除kPollPerSecondes_再乘kPollPerSeconds表示对齐值值kPollPerSeconds的整数倍，也就是时间会调整到当天的凌晨
                //因为除法会引发向下取整
                time_t thisPeriod = now / kRollPerSecondes_ * kRollPerSecondes_;
                if(thisPeriod != lastRoll_)//如果不等于lastRoll_,说明现在时间是新的一天了 生成一个新的日志文件
                {
                    rollFile();
                }
                else if(now - lastFlush_ > flushInterval_)//如果距离上次刷新缓冲区的时间超过了刷新时间间隔
                {
                    lastFlush_ = now;//刷新
                    file_->flush();//这里要调用file_的flush 因为调用LogFile的flush会死锁
                }
            }
        }
    }

    std::string LogFile::getLogFileName(const std::string &basename, time_t *now)
    {
        std::string filename;
        filename.reserve(basename.length() + 64);//预先分配空间
        filename = basename;

        char timebuf[32];
        struct tm t;
        *now = ::time(NULL);
        gmtime_r(now, &t);//获取当前UTC时间 r表示线程安全
//        //size_t strftime(char *strDest, size_t maxsize, const char *format, const  struct tm *timeptr);
        strftime(timebuf, sizeof(timebuf), ".%Y%m%d-%H%M%S.", &t);
        filename += timebuf;

        char pidBuf[32];
        snprintf(pidBuf, sizeof(pidBuf), "%d", ::getpid());
        filename += pidBuf;

        filename += ".log";

        return filename;
    }
}
}
//
// Created by jackson on 17-3-9.
//

#ifndef SIMPLENETWORDLIBRARY_LOGFILE_H
#define SIMPLENETWORDLIBRARY_LOGFILE_H

#include <string>
#include <memory>
#include "Mutex.h"

namespace Mu
{
namespace Base
{
    namespace FileUtil
    {
        class AppendFile;
    }

    class LogFile
    {
    public:
        //禁止复制
        LogFile(const LogFile &) = delete;
        LogFile& operator=(const LogFile &) = delete;

        //构造函数
        LogFile(const std::string &basename, int rollsize, int flushInterval = 3, int checkEveryN = 1024,//默认分割行数是1024
        bool threadSafe = true);//默认是线程安全的
        //析构函数
        ~LogFile();

        void append(const char *lineMsg, int len);//将长度为len的一行文本写入file_的缓冲区
        void flush();//刷新 将file_缓冲区中的数据写到磁盘
        bool rollFile();//滚动日志 返回true表示滚动日志成功 返回false表示失败

    private:
        void append_unlocked(const char *lineMsg, int len);//不加锁地将一行数据写入file_的缓冲区 效率比较高
        //日志文件的典型名字：logfile_test.20170309-115604.po.7743.log
        static std::string getLogFileName(const std::string &basename, time_t *now);

        const std::string basename_; //日志文件的basename
        const int rollSize_;        //日志文件达到rollSize时再生成一个新的日志文件
        const int checkEveryN_;     //日志文件每新写入checkEvery行就检查是否需要rollfile
        const int flushInterval_;   //日志写入的间隔时间

        int count_;     //计数器，检测是否需要换新的日志文件

        std::unique_ptr<MutexLock> mutex_; //锁
        time_t startOfPeriod_;          //开始记录日志时间（每天的凌晨0点）
        time_t lastRoll_;          //上次滚动日志（rollFile)时间
        time_t lastFlush_;          //上次写入日志时间
        std::unique_ptr<FileUtil::AppendFile> file_;   //智能指针 指向封装对一个日志文件的操作的AppendFile类

        const static int kRollPerSecondes_ = 60 * 60 * 24;  //时间为一天（意思是如果不考虑日志文件满的情况下。一天滚动一次一次日志)
    };
}
}

#endif //SIMPLENETWORDLIBRARY_LOGFILE_H

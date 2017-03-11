//
// Created by jackson on 17-3-6.
//

#ifndef SIMPLENETWORDLIBRARY_LOGGER_H
#define SIMPLENETWORDLIBRARY_LOGGER_H
//muduo库里面的日志使方法如下
//
//        这里定义了一个宏
//#define LOG_INFO if (muduo::Logger::logLevel() <= muduo::Logger::INFO) \
//  muduo::Logger(__FILE__, __LINE__).stream()
//返回的stream重载了一系列的运算符，使用方法如下
//LOG_INFO<<“info ...”;   // 使用方式
//上面那句其实就是
//        muduo::Logger(__FILE__, __LINE__).stream()<<“info”;
#include <cstring>
#include "TimeStamp.h"
#include "LogStream.h"

//调用过程实际是如下所示的
//Logger => Impl => LogStream => operator<< FixedBuffer => g_output => g_flush
//* 日记记录器只与日志流类(LogStream)、固定缓冲区(FixedBuffer)类有关、与日志文件类（LogFile）无关！！！
//* 只有当日志需要被记录到日志文件中的时候LogFile类才和Logger类有点关系
//muduo库里面的日志类封装相关的文件为Logging.h，Logging.cc，LogSrtream.h，LogSrtream.cc，附带一个StringPiece.h文件
namespace Mu
{
namespace Base
{
    class Logger
    {
    public:
        //日志级别
        enum LogLevel
        {
            TRACE,//追踪
            DEBUG,//调试
            INFO,//一般的信息
            WARN,//警告
            ERROR,//错误信息
            FATAL,//失败
            NUM_LOG_LEVELS,//级别个数6
        };

        //内部类：用来封装文件名（有的文件名是目录名后跟着文件名，这个类的作用就是在编译期间就取得文件名）
        class SourceFile
        {
        public:
            //模板，但是N是非类型参数
            template <int N>
            inline SourceFile(const char (&arr)[N])
            :data_(arr)
            {
                size_ = N - 1;
                //strrchr查找字符在数组中第一次出现的位置
               const char *slash = strrchr(data_, '/');
                if(slash)
                {
                    data_ = slash + 1;
                    size_ -= static_cast<int>(data_ - arr);
                }
            }

            SourceFile(const char *filename) : data_(filename)
            {
                const char *slash = strrchr(filename, '/');
                if(slash)
                {
                    data_ = slash + 1;
                }
                size_ = static_cast<int>(strlen(data_));
            }

            const char *data_;
            int size_;
        };
        //四个构造函数
        Logger(SourceFile file, int line);
        Logger(SourceFile file, int line, LogLevel level);
        Logger(SourceFile file, int line, LogLevel level, const char *func);
        Logger(SourceFile file, int line, bool toAbort);
        //析构函数
        ~Logger();
//muduo库里面的日志使方法如下
//这里定义了一个宏
//#define LOG_INFO if (muduo::Logger::logLevel() <= muduo::Logger::INFO) \
//muduo::Logger(__FILE__, __LINE__).stream()
//返回的stream重载了一系列的运算符，使用方法如下
//LOG_INFO<<“info ...”;   // 使用方式
//上面那句其实就是
//muduo::Logger(__FILE__, __LINE__).stream()<<“info”;
        //获取日志流对象
        LogStream& stream()
        {
            return impl_.stream_;
        }
        //static成员要在类外定义
        //返回日志等级
        static LogLevel Loglevel();
        //设置日志等级
        static void setLogLevel(LogLevel level);

        //简化输出函数的书写
        //这个函数用于决定日志输出到哪里，是日志文件还是控制台，如果是输出到日志文件中，可以调用LogFile的Append函数
        //默认调用的是defaultOutput函数
        typedef void (*outputFunc)(const char *msg, int len);
        //简化刷新缓冲区函数的书写 默认是defaultFlush
        typedef void (*flushFunc)();
        //设置输出函数
        static void setOutputFunc(outputFunc);
        //设置刷新函数
        static void setFlushFunc(flushFunc);

    private:
        //Loger类的内部嵌套类
        //impl类主要是负责日志的格式化
        class Impl
        {
        public:
            typedef Logger::LogLevel LogLevel;
            //构造函数
            Impl(LogLevel level, int old_errno, const SourceFile &file, int line);
            //格式化时间函数
            void formatTime();
            //刷新
            void finish();

            Timestamp time_;//Timestamp时间戳
            LogStream stream_;//LogStream类成员对象
            LogLevel level_;//日志等级
            int line_;//行号
            SourceFile basename_;//封装的文件名
        };
        //Logger只有这一个成员对象 Logger是个封装类 相当于把具体的操作都封装到Impl类中 而Impl类又封装了LogStream类
        Impl impl_;
    };
    //全局对象 日志的级别 在别的文件中定义
    extern Logger::LogLevel g_logLevel;

    //静态成员函数要在函数外定义 返回日志级别
    inline Logger::LogLevel Logger::Loglevel()
    {
        return g_logLevel;
    }
    //日志输出宏 定义了输出在哪个文件？哪一行？哪个函数？那种日志级别
    //无名对象在所在语句执行后就立即被析构，然后调用析构函数将缓冲区的内容输出
    //Mu::Base::Logger(__FILE__, __LINE__, Mu::Base::Logger::TRACE, __func__).stream返回的是一个LogStream对象
    //追踪
    #define LOG_TRACE if(Mu::Base::Logger::LogLevel() <= Mu::Base::Logger::TRACE)\
        Mu::Base::Logger(__FILE__, __LINE__, Mu::Base::Logger::TRACE, __func__).stream()
    //调试
    #define LOG_DEBUG if(Mu::Base::Logger::LogLevel() <= Mu::Base::Logger::DEBUG)\
        Mu::Base::Logger(__FILE__, __LINE__, Mu::Base::Logger::DEBUG, __func__).stream()
    //记录信息
    #define LOG_INFO if(Mu::Base::Logger::LogLevel() <= Mu::Base::Logger::INFO)\
       Mu::Base::Logger(__FILE__, __LINE__, Mu::Base::Logger::INFO, __func__).stream()
    //记录警告信息
    #define LOG_WARN Mu::Base::Logger(__FILE__, __LINE__, Mu::Base::Logger::WARN).stream()
    //记录错误信息
    #define LOG_ERROR Mu::Base::Logger(__FILE__, __LINE__, Mu::Base::Logger::ERROR).stream()
    //记录失败信息
    #define LOG_FATAL Mu::Base::Logger(__FILE__, __LINE__, Mu::Base::Logger::FATAL).stream()

    //false表示不会退出程序
    //记录系统错误
    #define LOG_SYSERR Mu::Base::Logger(__FILE__, __LINE__, false).stream()
    //true表示会退出程序
    //记录系统失败
    #define LOG_SYSFATAL Mu::Base::Logger(__FILE__, __LINE__, true).stream()
    //将错误转化成可读信息
    const char* strerror_tl(int savedErrno);

    //这个宏用来检测指针是否非空
    #define CHECK_NOTNULL(val)\
        Mu::Base::CheckNotNull(__FILE_, __LINE__,  "'" #val "' Must be non NULL", (val))

    //检测一个指针是否为空，如果是空，就在日志中记录
    template <typename T>
    T * CheckNotNull(Logger::SourceFile file, int line, const char *name, T *ptr)
    {
        if(ptr == NULL)
        {
            Logger(file, line, Logger::FATAL).stream() << name;
        }
        return ptr;
    }
}
}

#endif //SIMPLENETWORDLIBRARY_LOGGER_H

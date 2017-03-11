//
// Created by jackson on 17-3-7.
//

#include <assert.h>
#include "Logger.h"
#include "CurrentThread.h"

namespace Mu {
    namespace Base {

//__thread修饰符表示这是线程的局部存储，而不是全局变量
//每个线程都有各自对应的局部变量，读取或者修改的的都是自己的局部变量

//错误码的缓冲区
        __thread char t_errnobuf[512];
//时间的缓冲器
        __thread char t_time[32];
//上一秒
        __thread time_t t_lastSecond;

//将错误码转换成错误信息
        const char *strerror_tl(int savedErrno) {
            //通过标准错误的标号，获得错误的描述字符串 ，将单纯的错误标号转为字符串描述，方便用户查找错误
            return strerror_r(savedErrno, t_errnobuf, sizeof(t_errnobuf));
        }

//初始化全局的日志级别函数
        Logger::LogLevel initLogLevel() {
            if (::getenv("MUDUO_LOG_TRACE")) {
                return Logger::LogLevel::TRACE;
            } else if (::getenv("NUDUO_LOG_DEBUG")) {
                return Logger::LogLevel::DEBUG;
            } else {
                return Logger::LogLevel::INFO;
            }
        }

//初始化全局的日志级别
        Logger::LogLevel g_logLevel = initLogLevel();

//日志级别的名字数组，方便输出到缓存
        const char *LogLevelName[Logger::NUM_LOG_LEVELS] =
                {//不足6位的后面补空格 为了效率不用再次调用函数求长度 也为了输出的时候比较美观
                        "TRACE ",
                        "DEBUG ",
                        "INFO  ",
                        "WARN  ",
                        "ERROR ",
                        "FATAL ",
                };

//这是个帮助函数，可以在编译时获取字符串的长度
        class T {
        public:
            T(const char *str, unsigned len)
                    : str_(str),
                      len_(len) {
                assert(strlen(str) == len_);
            }

            const char *str_;
            const unsigned len_;
        };

//写数据到日志流中
        inline LogStream &operator<<(LogStream &s, T v) {
            s.append(v.str_, v.len_);
            return s;
        }

//写日志文件到日志留中
        inline LogStream &operator<<(LogStream &s, const Logger::SourceFile &file) {
            s.append(file.data_, file.size_);
            return s;
        }

//默认情况下。将日志输出到控制台
        void defaultOutput(const char *msg, int len) {
//  size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
//  其中，ptr：指向保存数据的指针；size：每个数据类型的大小；count：数据的个数；stream：文件指针
//  函数返回写入数据的个数。

            size_t n = fwrite(msg, 1, len, stdout);
            (void) n;
        }

//默认情况下，刷新控制台
        void defaultFlush() {
            fflush(stdout);
        }

//设置日志记录器的默认输出/刷新函数
//g_output 和 g_flush是全局变量 代表输入和刷新函数
        Logger::outputFunc g_output = defaultOutput;
        Logger::flushFunc g_flush = defaultFlush;
    }
}
//下面是Loger类的内部嵌套类Impl实现类
//impl类主要是负责日志的格式化
using namespace Mu;
using namespace Base;
        Logger::Impl::Impl(LogLevel level, int savedError, const SourceFile &file, int line)
                : time_(Timestamp::now()),
                  stream_(),
                  level_(level),
                  line_(line),
                  basename_(file) {
            //格式化时间
            formatTime();

            //缓存当前的线程id
            CurrentThread::tid();

            //记录当前线程的id和日志级别
            stream_ << T(CurrentThread::tidString(), 6);
            stream_ << T(LogLevelName[level], 6);

            //如果有错误发生 那么应该记录错误并输出
            if (savedError != 0) {
                stream_ << strerror_tl(savedError) << "(errno=" << savedError << ") ";
            }
        }

        void Logger::Impl::formatTime() {
            int64_t microSecondsSinceEpoch = time_.microSecondsSinceEpoch();
            time_t seconds = static_cast<time_t>(microSecondsSinceEpoch / Timestamp::kMicroSecondsPerSecond);
            int microSeconds = static_cast<int>(microSecondsSinceEpoch % Timestamp::kMicroSecondsPerSecond);

            //时间格式化
            //如果与上次调用这个函数的时间间隔不超过1s.则秒数没必要重新求 用上次的就行
            if (seconds != t_lastSecond) {
                t_lastSecond = seconds;
                struct tm tm_time;
                ::gmtime_r(&seconds, &tm_time);

                int len = snprintf(t_time, sizeof(t_time), "%4d%02d%02d %02d:%02d:%02d",
                                   tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour,
                                   tm_time.tm_min, tm_time.tm_sec);
                assert(len == 17);
                (void) len;
            }
            Fmt us(".%06dZ", microSeconds);
            assert(us.length() == 8);
            //LogStream类重载运算符，把格式化后的日期输出到缓冲区
            //t_time是线程特有的时间缓存区
            stream_ << T(t_time, 17) << T(us.data(), us.length());
        }

//刷新，其实是记录基本文件名和行数
        void Logger::Impl::finish() {
            stream_ << " - " << basename_ << ":" << line_ << "\n";
        }

//Logger的构造函数，其实都是构造Impl对象，只有file和line参数时日志类型默认时INFO
        Logger::Logger(SourceFile file, int line)
                : impl_(INFO, 0, file, line) {}

        Logger::Logger(SourceFile file, int line, LogLevel level) :
                impl_(level, 0, file, line) {}

//构造的是否顺便输出函数名称
        Logger::Logger(SourceFile file, int line, LogLevel level, const char *func)
                : impl_(level, 0, file, line) {
            impl_.stream_ << func << " ";
        }

//如果toAbort是真，则级别为FATAL,否则为ERROR
        Logger::Logger(SourceFile file, int line, bool toAbort)
                : impl_(toAbort ? FATAL : ERROR, errno, file, line) {
        }

//析构函数
        Logger::~Logger() {
            //刷新 标志着一句日志信息的结束
            impl_.finish();
            //取出LogStream缓冲区的内容放到buf
            const LogStream::Buffer &buf(stream().buffer());
            //输出 g_output有一个默认的输出stdout
            g_output(buf.data(), buf.length());
            //如果是FATAL
            if (impl_.level_ == FATAL) {
                //刷新缓冲区
                g_flush();
                //终止程序
                abort();
            }
        }

//设置日志级别
        void Logger::setLogLevel(LogLevel level) {
            g_logLevel = level;
        }

//设置输出函数
        void Logger::setOutputFunc(outputFunc out) {
            g_output = out;
        }

//设置刷新函数
        void Logger::setFlushFunc(flushFunc flush) {
            g_flush = flush;
        }

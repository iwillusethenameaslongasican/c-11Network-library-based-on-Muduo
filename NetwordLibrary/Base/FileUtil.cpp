//
// Created by jackson on 17-3-9.
//


#include <cassert>
#include "FileUtil.h"
#include "Logger.h"

namespace Mu
{
namespace Base
{
    namespace FileUtil
    {
        AppendFile::AppendFile(const std::string &filename)
        :fp_(fopen(filename.c_str(), "ae")),//'e‘代表O_CLOEXEC
         writtenBytes_(0)
        {
            assert(fp_);
            ::setbuffer(fp_, buf_, sizeof(buf_));//文件指针的缓冲区为64K
        }

        AppendFile::~AppendFile()
        {
            ::fclose(fp_);
        }
        //不是线程安全的 需要外部加锁
        void AppendFile::append(const char *lineMsg, int len)
        {
            size_t n = write(lineMsg, len);
            size_t remain = len - n;
            while(remain > 0)//如果数据没写完 就进入循环继续写 直到写完len字节数据
            {
                size_t m = write(lineMsg, remain);
                if(m == 0)
                {
                    int err = ferror(fp_);
                    if(err)
                    {
                        fprintf(stderr, "AppendFile::append failed\n", strerror_tl(err));
                    }
                    break;
                }
                n += m;
                remain -= m;
            }
            writtenBytes_ += len;
        }
        //刷新缓冲区
        void AppendFile::flush()
        {
            ::fflush(fp_);
        }

        size_t AppendFile::write(const char *lineMsg, int len)
        {
            return ::fwrite_unlocked(lineMsg, 1, len, fp_);//不加锁的方式写入,效率高,非线程安全，默认fwrite是自动加锁的
        }
    }
}
}
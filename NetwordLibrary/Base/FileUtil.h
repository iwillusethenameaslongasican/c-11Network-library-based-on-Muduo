//
// Created by jackson on 17-3-9.
//

#include <cstdio>
#include <string>


#ifndef SIMPLENETWORDLIBRARY_FILEUTIL_H
#define SIMPLENETWORDLIBRARY_FILEUTIL_H

#endif //SIMPLENETWORDLIBRARY_FILEUTIL_H

namespace Mu
{
namespace Base
{
    namespace FileUtil
    {
        class AppendFile
        {
        public:
            //禁止复制
            AppendFile(const AppendFile &) = delete;
            AppendFile& operator=(const AppendFile &) = delete;

            AppendFile(const std::string  &filename);
            ~AppendFile();

            void append(const char *lineMsg, int len);
            void flush();
            size_t writtenBytes() const
            {
                return writtenBytes_;
            }

        private:
            size_t write(const char *lineMsg, int len);

            FILE *fp_;//文件指针
            char buf_[64 * 1024];//64KDE缓冲区
            size_t writtenBytes_; //已经写入的字节数
        };
    }
}
}
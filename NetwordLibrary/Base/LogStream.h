//
// Created by jackson on 17-3-8.
//

#ifndef SIMPLENETWORDLIBRARY_LOGSTREAM_H
#define SIMPLENETWORDLIBRARY_LOGSTREAM_H

#include "StringPiece.h"
#include <cstddef>
#include <cstring>
#include <string>

namespace Mu
{
namespace Base
{
   namespace detail
   {
       //定义两个缓冲区大小

       //小的缓冲区大小
       const int kSmallBuffer = 4000;
       //大的缓冲区大小
       const int kLargeBuffer = 4000 * 1000;

       //固定大小的buffer类
       template <int SIZE>
       class FixedBuffer
       {
       public:
           //禁止复制
           FixedBuffer(const FixedBuffer &) = delete;
           FixedBuffer& operator=(const FixedBuffer &) = delete;

           FixedBuffer(): cur_(data_) {}
           ~FixedBuffer() {}
            //添加数据
           void append(const char *buf, size_t len)
           {
               //这里用boost::implicit_cast更好，因为可以阻止基类型向派生类型转换
               //static_cast太过强大，但是我c++标准库中并没有implicit_cast功能的函数
               if(static_cast<size_t>(avail()) > len)
               {//当前可用的缓冲区大小大于len
                   memcpy(cur_, buf, len);//把字符串复制到缓冲区后面
                   cur_ += len;//更新当前缓冲区指针
               }
               //FIXME: 如果缓冲区空间不够，提供解决方案
           }

           //返回缓冲区头部
           const char * data() const {
               return data_;
           }

           //返回缓冲区可用的空间
           int avail() const
           {
               return static_cast<int>(end() - cur_);
           }

           //返回已用空间
           int length() const
           {
               return static_cast<int>(cur_ - data_);
           }

           //返回当前缓冲区读写指针
           char *current()
           {
               return cur_;
           }

           //增加
           void add(size_t len)
           {
               cur_ += len;
           }

           //重置缓冲区当前读写位置指针，使它指向缓冲区开头
           void reset()
           {
               cur_ = data_;
           }

           //把缓冲区数据清0 缓冲区空间并没有被释放
           void bzero()
           {
               ::bzero(data_, sizeof(data_));
           }

           //在数据后面加个结束符,用于调试字符串
           const char *debugString();

           //把数据构造一个string对象出来
           std::string asString() const
           {
               return std::string(data_);
           }
           Mu::Base::StringPiece toStringPiece() const
           {
               return StringPiece(data_, length());
           };

       private:
           //返回缓冲区的后一个位置
           const char* end() const
           {
               return (data_ + sizeof(data_));
           }

           //固定大小的缓冲区
           char data_[SIZE];
           //指向缓冲区当前读写位置的指针
           char *cur_;
       };
   }

    //LogStream：包含一个FixedBuffer类型的成员变量buffer_
    //logtream就是负责将数值类型，字符串格式化写入FixedBuffer类型的成员buff_中
    //封装了<<运算符
    class LogStream
    {

        typedef LogStream Self;
    public:
        typedef detail::FixedBuffer<detail::kSmallBuffer> Buffer;
        //禁止复制
        LogStream(const LogStream &) = delete;
        Self& operator=(const LogStream &) = delete;

        //只需要默认构造函数就行
        LogStream(){}
        //下面的函数都用于重载<<操作符 全部将数据存放于缓冲区中
        Self& operator<<(bool b)
        {
            buffer_.append(b ? "1" : "0", 1);
            return *this;
        }
        Self& operator<<(short);
        Self& operator<<(unsigned short);
        Self& operator<<(int);
        Self& operator<<(unsigned int);
        Self& operator<<(long);
        Self& operator<<(unsigned long);
        Self& operator<<(long long);
        Self& operator<<(unsigned long long);
        //存放指针
        Self& operator<<(const void *);

        Self& operator<<(float f)
        {
            *this << static_cast<double>(f);
            return *this;
        }
        Self& operator<<(double);
        //单个字符
        Self& operator<<(char c)
        {
            buffer_.append(&c, 1);
            return *this;
        }
        //c字符串
        Self& operator<<(const char *str)
        {
            if(str == NULL)
            {
                buffer_.append("(NULL)", 6);
            }
            else
            {
                buffer_.append(str, strlen(str));
            }
            return *this;
        }
        Self& operator<<(const unsigned char *str)
        {//reinterpret_cast用在任意指针（或引用）类型之间的转换；以及指针与足够大的整数类型之间的转换；从整数类型（包括枚举类型）到指针类型，无视大小
            //错误的使用reinterpret_cast很容易导致程序的不安全，只有将转换后的类型值转换回到其原始类型，这样才是正确使用reinterpret_cast方式。
            //reinterpret_cast不能像const_cast那样去除const修饰符
            return *this << reinterpret_cast<const char *>(str);
        }

        Self& operator<<(const std::string &s)
        {
            buffer_.append(s.c_str(), s.size());
            return *this;
        }
        Self& operator<<(const StringPiece &s)
        {
            buffer_.append(s.data(), s.size());
            return *this;
        }

        Self& operator<<(const Buffer &buffer)
        {
            *this << buffer.toStringPiece();
            return *this;
        }

        //包装了buffer的append函数
        void append(const char *data, int len)
        {
            buffer_.append(data, len);
        }
        //返回缓冲区
        const Buffer& buffer() const
        {
            return buffer_;
        }

        //重置缓冲区 包装了buffer的reset接口
        void resetBuffer()
        {
            buffer_.reset();
        }


    private:
        //静态检查
        void staticCheck();

        //格式化整数
        template <typename T>
        void formatInteger(T);

        Buffer buffer_;

        //用来保证缓冲区不溢出
        //这个常量表示了最大的数值类型能占用的空间的大小
        static const int kMaxNumbericSize = 32;
    };

    //Fmt 类：一个格式化工具类,构造函数就两个参数，一个是格式化样式，一个是要被格式化的对象-数值类型
    //LogStream类型可以直接通过<<操作将Fmt 写入缓冲区buff_  : ./LogStream.h:inline LogStream& operator<<(LogStream& s, const Fmt& fmt)
    //使用方法：
   //muduo::LogStream os;
    //os << muduo::Fmt("%4.2f", 1.2);
    class Fmt
    {
    public:
        template <typename T>
                Fmt(const char *fmt, T val);

        const char *data() const
        {
            return buf_;
        }

        int length() const
        {
            return length_;
        }

    private:
        char buf_[32];
        int length_;

    };

    //重载<< 存储fmt实例到LogStream
    inline LogStream& operator<<(LogStream &log, const Fmt &fmt)
    {
        log.append(fmt.data(), fmt.length());
    }
}
}

#endif //SIMPLENETWORDLIBRARY_LOGSTREAM_H

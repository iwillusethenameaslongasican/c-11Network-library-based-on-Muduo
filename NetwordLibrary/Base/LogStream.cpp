//
// Created by jackson on 17-3-8.
//

#include "LogStream.h"
#include <algorithm>
#include <assert.h>


namespace Mu {
    namespace Base {
        namespace detail {
            //数字字符
            const char digits[] = "9876543210123456789";

            //字符'0'
            const char *zero = digits + 9;

            static_assert((sizeof(digits) == 20), "digits size != 20");

            //16进制的字符
            const char digitsHex[] = "0123456789ABCDEF";
            static_assert((sizeof(digitsHex) == 17), "digitsHex size != 17");

            //把数字转换成字符串
            template<typename T>
            size_t convert(char buf[], T value) {
                char *p = buf;
                T t = value;

                do {
                    //取余数
                    int x = static_cast<int>(t % 10);
                    //求商
                    t /= 10;
                    //zero将数字转换成字符串,zero指针指向的字符是0，再偏移lsd个位置可以得到相应的字
                    *p++ = zero[x];
                } while (t != 0);
                //如果数字小于0
                //比如-123会转换成321-
                if (value < 0) {
                    *p++ = '-';
                }
                *p = '\0';//添加字符串结束符
                //由于buf中存储的顺序与数字的实际顺序是相反的 所以要reverse
                std::reverse(buf, p);

                //返回被转换了的数字的位数
                return p - buf;
            }

            //把16进制的数字转换成字符串
            //uintptr_t类型对于32位平台来说就是unsigned int
//    intptr_t 和uintptr_t 类型用来存放指针地址。它们提供了一种可移植且安全的方法声明指针，
// 而且和系统中使用的指针长度相同，对于把指针转化成整数形式来说很有用。
            //对于64位平台来说就是unsigned long in
            size_t convertHex(char buf[], uintptr_t value) {
                uintptr_t t = value;
                char *p = buf;

                do {
                    int x = static_cast<int>(t % 16);
                    t /= 16;
                    *p++ = digitsHex[x];
                } while (t != 0);

                *p = '\0';
                std::reverse(buf, p);
                return p - buf;
            }

            template class FixedBuffer<kSmallBuffer>;
            template class FixedBuffer<kLargeBuffer>;
        }
    }
}

using namespace Mu;
using namespace Base;
using namespace detail;

//在数据后面加个结束符,用于调试字符串
template <int SIZE>
const char * FixedBuffer<SIZE>::debugString()
{
    *cur_ = '\0';
    return data_;
}

//静态检查，用于检查一些类型的大小
void LogStream::staticCheck()
{
    //返回目标类型在十进制下可以表示的最大位数
    static_assert(kMaxNumbericSize - 10 > std::numeric_limits<double>::digits10, "staticCheck double");
    static_assert(kMaxNumbericSize - 10 > std::numeric_limits<long double>::digits10, "staticCheck long double");
    static_assert(kMaxNumbericSize - 10 > std::numeric_limits<long>::digits10, "staticCheck long");
    static_assert(kMaxNumbericSize - 10 > std::numeric_limits<long long>::digits10, "staticCheck long long");
}


//格式化整形 将数值转换成字符串，并添加到buffer_中
template <typename T>
void LogStream::formatInteger(T val)
{
    if(buffer_.avail() >= kMaxNumbericSize)
    {
        size_t len = convert(buffer_.current(), val);
        buffer_.add(len);
    }
}

//下面是一系列的运算符<<重载函数
LogStream& LogStream::operator<<(int val)
{
    formatInteger(val);
    return *this;
}

LogStream& LogStream::operator<<(unsigned int val)
{
    formatInteger(val);
    return *this;
}

LogStream& LogStream::operator<<(short val)
{
    *this << static_cast<int>(val);
    return *this;
}

LogStream& LogStream::operator<<(unsigned short val)
{
    *this << static_cast<int>(val);
    return *this;
}


LogStream& LogStream::operator<<(long val)
{
    formatInteger(val);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long val)
{
    formatInteger(val);
    return *this;
}

LogStream& LogStream::operator<<(long long val)
{
    formatInteger(val);
    return *this;
}

//将普通数据转换成16进制存储（多用于存储指针）
LogStream& LogStream::operator<<(const void *p)
{
    uintptr_t v = reinterpret_cast<uintptr_t>(p);
    //保证了任意的基础类型都能狗存放在缓冲区中而不至于溢出
    if(buffer_.avail() >= kMaxNumbericSize)
    {
        char *cur = buffer_.current();
        cur[0] = '0';
        cur[1] = 'x';
        size_t  len = convertHex(cur + 2, v);
        buffer_.add(len + 2);
    }
    return *this;
}

LogStream& LogStream::operator<<(double v)
{
    if(buffer_.avail() >= kMaxNumbericSize)
    {
        //%g double  型的参数会自动选择以%f 或%e 的格式来打印，其标准是根据打印的数值及所设置的有效位数来决定。
        //.12表示小数位数
        int len = snprintf(buffer_.current(), kMaxNumbericSize, "%.12g", v);
        buffer_.add(len);
    }
    return *this;
}

//格式化类
template <typename T>
Fmt::Fmt(const char *fmt, T val)
{
    using namespace std;
    //静态断言 T类型是否时算术类型（整形，浮点型等类型） 如果是用户自定义类型 则不能格式化
    static_assert(std::is_arithmetic<T>::value == true, "is_arithmetic");

    //格式化
    length_ = snprintf(buf_, sizeof(buf_), fmt, val);
    assert(static_cast<size_t >(length_) < sizeof(buf_));
}

//显式实例化（explicit instantiation）
//作用是具现化模板 不可以提供新的函数体 防止用户误用
//采用模板显示实例化可以减小编译器实例化展开的开销

template Fmt::Fmt(const char *fmt, char);

template Fmt::Fmt(const char *fmt, short);
template Fmt::Fmt(const char *fmt, unsigned short);
template Fmt::Fmt(const char *fmt, int);
template Fmt::Fmt(const char *fmt, unsigned int);
template Fmt::Fmt(const char *fmt, long);
template Fmt::Fmt(const char *fmt, unsigned long);
template Fmt::Fmt(const char *fmt, long long);
template Fmt::Fmt(const char *fmt, unsigned long long);

template Fmt::Fmt(const char *fmt, float);
template Fmt::Fmt(const char *fmt, double);

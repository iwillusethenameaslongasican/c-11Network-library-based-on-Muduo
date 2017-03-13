//
// Created by jackson on 17-3-10.
//

#ifndef SIMPLENETWORDLIBRARY_BUFFER_H
#define SIMPLENETWORDLIBRARY_BUFFER_H
//应用缓冲区 （专门用于网络数据的读取和发送）
//假如这个框架用于套接字读取，那么框架把套接字读取的数据写入到writerIndex指示的位置
//而用户从readerIndex的位置开始读取数据，readerIndex和writerIndex直接存放了可供读取的有效数据
#include "../Base/StringPiece.h"
#include "Endian.h"
#include <pthread.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <cstring>

namespace Mu
{
namespace Net
{
// 一个缓冲区由三个部分组成：预留区、读取区，写入区，
// 0～readerIndex之间是预留区
// readerIndex～writerIndex之间是读取区
// writerIndex～size之间是写入区


/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// 预留区              可读数据               可写数据
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode
        //可以复制
//        muduo的缓冲区Buffer类不是线程安全的，因为它是每个连接私有的，不需要锁的操作
        class Buffer
        {
        public:
            //起始的时候，预留区为8字节
            const static size_t kCheapPrepend = 8;
            //初始时缓冲区的大小
            const static size_t kInitialSize = 1024;
            //初始时可读区域为0字节
            //可写区域为kInitialSize字节 代表有整个缓冲区大小的空间都可以写入
            Buffer(int initialSize = kInitialSize)
            :   buffer_(kCheapPrepend + initialSize),
                readerIndex_(kCheapPrepend),
                writerInedx_(kCheapPrepend)
            {
                assert(readableBytes() == 0);
                assert(writableBytes() == initialSize);
                assert(prependableBytes() == kCheapPrepend);
            }

            //数据交换
            void swap(Buffer &buffer)
            {
                buffer_.swap(buffer.buffer_);
                std::swap(readerIndex_, buffer.readerIndex_);
                std::swap(writerInedx_, buffer.writerInedx_);
            }
            //可读缓冲区的数据数
            size_t readableBytes() const
            {
                return (writerInedx_ - readerIndex_);
            }
            //可写缓冲区的数据数
            size_t writableBytes() const
            {
                return (buffer_.size() - writerInedx_);
            }
            //预留区大小
            size_t prependableBytes() const
            {
                return (readerIndex_);
            }
            //返回可读区域的起始位置
            const char *peek() const
            {
                return &*(buffer_.begin() + readerIndex_);
            }
            //在可读区域寻找\r\n
            const char *findCRLF() const
            {
                const char *crlf = std::search(peek(), beginWrite(), kCRLF, kCRLF + 2);
                return (crlf == beginWrite() ? NULL : crlf);
            }
            //在可读区域指定的起始位置查找\r\n
            const char *findCRLF(const char *start) const
            {
                assert(start >= peek());
                assert(start < beginWrite());
                const char *crlf = std::search(start, beginWrite(), kCRLF, kCRLF + 2);
                return (crlf == beginWrite() ? NULL : crlf);
            }
            //在可读区域查找\n 即一行的结尾
            const char * findEOL() const
            {
               //功能：从buf所指内存区域的前count个字节查找字符ch。
               // 说明：当第一次遇到字符ch时停止查找。如果成功，返回指向字符ch的指针；否则返回NULL。
                const void *eol = ::memchr(peek(), '\n', readableBytes());
                return static_cast< const char *>(eol);
            }
            //在可读区域指定的起始位置查找\n
            const char * findEOL(const char *start) const
            {
                assert(start >= peek());
                assert(start < beginWrite());
                const void *eol = ::memchr(start, '\n', beginWrite() - start);
                return static_cast<const char *>(eol);
            }

            //将缓冲区的可读指针向前移动len字节 并不真正读取数据
            //因为如果这个函数读取并返回数据的话用户可能会调用
            //string str(retrieve(readableBytes()), readableBytes()) 这个函数的执行顺序不一定可能造成未定义行为
            //一般的做法是先从可读区域获取数据，然后再调用这个函数，移动可读区域的指针
            //移动可读区域的指针
            void retrieve(size_t len)
            {
                assert(len <= readableBytes());
                if(len < readableBytes())
                {
                    readerIndex_ += len;
                }
                else//len == readableBytes() 则说明可读区域已空 readerIndex和writerIndex都复位
                {
                    retrieveAll();
                }
            }
            //把可读区域的指针移到指定的位置
            void retrieveUntil(const char *end)
            {
                assert(peek() <= end);
                assert(end <= beginWrite());
                retrieve(end - peek());
            }
            //将readerIndex和WriterIndex复位
            void retrieveAll()
            {
                readerIndex_ = kCheapPrepend;
                writerInedx_ = kCheapPrepend;
            }
            void retrieveInt64()
            {
                retrieve(sizeof(int64_t));
            }
            void retrieveInt32()
            {
                retrieve(sizeof(int32_t));
            }
            void retrieveInt16()
            {
                retrieve(sizeof(int16_t));
            }
            void retrieveInt8()
            {
                retrieve(sizeof(int8_t));
            }
            //将指定长度的数据取出当做字符串
            std::string retrieveAsString(size_t len)
            {
                assert(len <= readableBytes());
                std::string str(peek(), peek() + len);
                retrieve(len);
                return str;
            }
            std::string retrieveAllAsString()
            {
                return retrieveAsString(readableBytes());;
            }
            // 同retrieveAllAsString，不过StringPiece并不真正存储字符串，他只是一个包装
            // 这个函数也可以说是把可读区域的数据都当成字节序列，不区分类型
            Mu::Base::StringPiece toStringPiece() const
            {
                return Mu::Base::StringPiece(peek(), static_cast<int>(readableBytes()));
            }

            //写入数据
            void append(const Mu::Base::StringPiece &str)
            {
                append(str.data(), str.size());
            }
            //写入数据
            void append(const char *data, size_t len)
            {
                //确保写入区的空间 如果不够就要扩充
                ensureWritableBytes(len);
                //复制数据
                std::copy(data, data + len, beginWrite());
                //一定写入区的指针
                hasWritten(len);
            }
            //写入数据
            void append(const void *data, size_t len)
            {
                append(static_cast<const char *>(data), len);
            }

            //确保写入区域的大小
            void ensureWritableBytes(size_t len)
            {
                if(writableBytes() < len)
                {
                    //扩展空间
                    makeSpace(len);
                }
                assert(writableBytes()  >= len);
            }
            //获取写入区的指针
            char *beginWrite()
            {
                return &*(buffer_.begin() + writerInedx_);
            }
            //获取写入区的起始指针
            const char *beginWrite() const
            {
                return &*(buffer_.begin() + writerInedx_);
            }
            //移动写入区的指针(向前移动，表示写入数据）
            void hasWritten(size_t len)
            {
                assert(len <= writableBytes());
                writerInedx_ += len;
            }
            //移动写入区指针（向后移动，表示撤销写入，回退数据）
            void unWrite(size_t len)
            {
                assert(len <= readableBytes());
                writerInedx_ -= len;
            }
            //写入一个Int64_t类型的数据，先把数据转换成网络字节顺序，再写入
            void appendInt64(int64_t x)
            {
                int64_t  be64 = sockets::hostToNetwork64(x);
                append(&be64, sizeof(be64));
            }
            //写入一个Int32_t类型的数据
            void appendInt32(int32_t x)
            {
                int32_t be32 = sockets::hostToNetwork32(x);
                append(&be32, sizeof(be32));
            }
            //写入一个Int16_t类型的数据
            void appendInt16(int16_t x)
            {
                int16_t be16 = sockets::hostToNetwork16(x);
                append(&be16, sizeof(be16));
            }
            //写入一个Int8_t类型的数据
            void appendInt8(int8_t x)
            {
                append(&x, sizeof(x));
            }
            //读取一个Int64_t类型的数据 先把数据从网络字节序转换成主机字节序 然后再返回
            //同时移动读取区指针
            int64_t readInt64()
            {
                int64_t result = peekInt64();
                retrieveInt64();
                return result;
            }
            int64_t peekInt64() const
            {
                assert(readableBytes() >= sizeof(int64_t));
                int64_t be64 = 0;
                ::memcpy(&be64, peek(), sizeof(be64));
                return sockets::network64ToHost(be64);
            }
            //读取一个int32_t类型的数据
            int32_t readInt32()
            {
                int32_t result = peekInt32();
                retrieveInt32();
                return result;
            }
            int32_t peekInt32() const
            {
                assert(readableBytes() >= sizeof(int32_t));
                int32_t be32 = 0;
                ::memcpy(&be32, peek(), sizeof(int32_t));
                return sockets::network32ToHost(be32);
            }
            //读取一个int16_t类型的数据
            int16_t readInt16()
            {
                int16_t result = peekInt16();
                retrieveInt16();
                return result;
            }
            int16_t peekInt16() const
            {
                assert(readableBytes() >= sizeof(int16_t));
                int16_t be16 = 0;
                ::memcpy(&be16, peek(), sizeof(int16_t));
                return sockets::network16ToHost(be16);
            }
            //读取一个int8_t类型的数据
            int8_t readInt8()
            {
                int8_t result = peekInt8();
                retrieveInt8();
                return result;
            }
            int8_t peekInt8() const
            {
                assert(readableBytes() >= sizeof(int8_t));
                int8_t be8 = *peek();
                return be8;
            }
            //往预留区写入int64_t的数据，要注意先把它转换成网络字节序
            void prependInt64(int64_t x)
            {
                int64_t be64 = sockets::hostToNetwork64(x);
                prepend(&be64, sizeof(be64));
            }
            //往预留区写入int32_t类型的数据
            void prependInt32(int32_t x)
            {
                int32_t be32 = sockets::hostToNetwork32(x);
                prepend(&be32, sizeof(be32));
            }
            //往预留区写入int16_t类型的数据
            void prependInt16(int16_t x)
            {
                int16_t be16 = sockets::hostToNetwork16(x);
                prepend(&be16, sizeof(be16));
            }
            //往预留区写入int8_t类型的的数据
            void prependInt8(int8_t x)
            {
                prepend(&x, sizeof(x));
            }
            // 与append相对应，append在writerIndex_所指向的缓冲区写入数据（即在可读区域后面写入数据）
            // 而prepend则是在readerIndex_所指向的缓冲区的前面写入数据（即在可读区域前面写入数据）
            void prepend(const void *data, size_t len)
            {
                assert(len <= prependableBytes());
                //读取区指针先往前移len位，到达写入数据后读取区指针应该在的位置上
                readerIndex_ -= len;
                const char *ch = static_cast<const char *>(data);
                std::copy(ch, ch + len, &*(buffer_.begin() + readerIndex_));
            }
            //空间收缩，在原来的基础上把缓冲区收缩成readableBytes()+reserve大小，并保留原本已写入的数据
            void shrink(size_t reserve)
            {
                Buffer other;//生成临时对像，保存readable内容，然后和自身交换，该临时对象再析构掉
                other.ensureWritableBytes(readableBytes() + reserve);//确保有足够的空间
                //复制原来的数据
                other.append(toStringPiece());
//                //other调用ensutrWritableBytes()的时候会调用resize重新分配空间
//                //而vector的增长机制会使本来的空间加倍 这里调用c++11的shark_to_fit来释放掉没有使用到的空间
//                other.buffer_.shrink_to_fit();
                //交换
                swap(other);
            }

            //返回缓冲区的空间大小
            size_t internalCapaity() const
            {
                return buffer_.capacity();
            }
            //从套接字（文件描述符）中读取数据，然后放在缓冲区中，savedErrno保存错误码
            ssize_t readFd(int fd, int *savedErrno);
        private:
            //分配或者调整空间
            void makeSpace(size_t len)
            {   //如果空间真的不足
                if(writableBytes() + prependableBytes() < kCheapPrepend + len)
                {
                    //就重新分配空间，vector的内存分配机制会导致空间加倍
                    buffer_.resize(writerInedx_ + len);
                    //fixme:这里可以挪动内部元素
                }
                else//如果剩余空间足够 但是需要向前数据向前挪移才能方便使用
                {
                    // move readable data to the front, make space inside buffer
                    // readerIndex_前面的空间太多，而writerIndex_之后的空间又不足
                    // 需要将readerIndex_与writerIndex_之间的数据往前面移动，让writerIndex_之后有足够的空间
                    assert(kCheapPrepend < readerIndex_);
                    size_t readable = readableBytes();
                    std::copy(&*(buffer_.begin() + readerIndex_),
                              &*(buffer_.begin() + writerInedx_),
                                 &*(buffer_.begin() + kCheapPrepend));
                    readerIndex_ = kCheapPrepend;
                    writerInedx_ = kCheapPrepend + readable;
                    assert(readable = readableBytes());
                }
            }

            std::vector<char> buffer_;
            size_t readerIndex_;
            size_t writerInedx_;

            static const char kCRLF[];
        };
}
}

#endif //SIMPLENETWORDLIBRARY_BUFFER_H

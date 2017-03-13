//
// Created by jackson on 17-3-10.
//

#include <sys/uio.h>
#include "Buffer.h"
#include "Socketopts.h"

using namespace Mu;
using namespace Net;

const char Buffer::kCRLF[] = "\r\n";

const size_t Buffer::kCheapPrepend;
const size_t Buffer::kInitialSize;
//结合栈上空间，避免内存使用过大，提高内存使用率
//如果有10K个连接，每个连接就分配64K缓冲区的话，将占用640M内存
//而大多数时候，这些缓冲区的使用率很低
ssize_t Buffer::readFd(int fd, int *savedErrno)
{//节省一次ioctl系统调用(获取当前有多少可读数据）
    //为什么这么说?因为我们准备了足够大的extrabuf，那么我们就不需要使用ioctl取查看fd有多少可读字节数了
    char extrabuf[65535];
    struct iovec vec[2];
    const size_t writable = writableBytes();
    vec[0].iov_base = beginWrite();
    vec[0].iov_len = writable;
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof(extrabuf);
    //我们最多能读取2×65535字节 也就是128k-1字节
    const ssize_t n = ::readv(fd, vec, 2);

    if(n < 0)
    {
        *savedErrno = errno;
    }
    else if(static_cast<size_t >(n) <= writable)//第一块缓冲区足够容纳
    {
        writerInedx_ += n;
    }
    else//当前缓冲区不够容纳 所以有些数据被存放到了extrabuf中
    {
        writerInedx_ = buffer_.size();//先更新当前的writerIndex_
        append(extrabuf, n - writable);//再把extrabuf中的数据加入buffer_中
    }
    return n;
}

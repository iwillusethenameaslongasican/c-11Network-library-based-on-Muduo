//
// Created by jackson on 17-3-3.
//

#ifndef SIMPLENETWORDLIBRARY_SOCKETOPTS_H
#define SIMPLENETWORDLIBRARY_SOCKETOPTS_H

#include <netinet/in.h>

namespace Mu
{
namespace Net
{
    namespace sockets
    {
        //把套接字设置成非阻塞和执行exec时关闭
        void setNotBlockAndCloseOnExec(int fd);
        //生成一个非阻塞且执行exec时关闭的套接字
        int createNotBlockAndCloseOnExecOrDie();
        //关闭套接字描述符，在Socket的析构函数中调用
        void close(int fd);
        //把套接字描述符绑定到一个地址　或者出错返回
        void bindOrDie(int fd, const struct sockaddr_in &Address);
        //把主动套接字转换成被动套接字，或者出错返回
        void listenOrDie(int fd);
        //取出已连接队列中的连接
        int accept(int fd, struct sockaddr_in *peerAddress);
        //关闭套接字描述符的写端
        void shutDownWrite(int fd);

        //把sockaddr_in　*转换成　sockaddr*
        const struct sockaddr* sockAddrCast(const struct sockaddr_in *addr) const;
        struct sockaddr* sockAddrCast(struct sockaddr_in *addr);

    }
}
}

#endif //SIMPLENETWORDLIBRARY_SOCKETOPTS_H

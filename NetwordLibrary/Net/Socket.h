//
// Created by jackson on 17-3-3.
//

#ifndef SIMPLENETWORDLIBRARY_SOCKET_H
#define SIMPLENETWORDLIBRARY_SOCKET_H


#include "InetAddress.h"

namespace Mu
{
namespace Net
{
    class Socket
    {
    public:
        explicit Socket(int sockfd) : sockfd_(sockfd) {}
        //禁止复制
        Socket(const Socket &) = delete;
        Socket&operator=(const Socket &) = delete;
        ~Socket();

        int fd() const
        {
            return sockfd_;
        }
        //绑定地址
        void bindAddress(const InetAddress &localAddress);
        //把主动套接字转换成被动套接字
        void listen();

        int accept(InetAddress &peerAddress);
        //不使用close，而应该使用shutdownwrite关闭写端，以接收对方放出的数据
        void shutDownWrite();
        //启动或者关闭重复使用地址
        void setReuseAddress(bool on);

    private:
        const int sockfd_;
    };
}
}


#endif //SIMPLENETWORDLIBRARY_SOCKET_H

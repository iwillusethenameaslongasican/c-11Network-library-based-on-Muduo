//
// Created by jackson on 17-3-3.
//


#include <netinet/in.h>
#include <string.h>
#include "Socket.h"
#include "Socketopts.h"

using namespace Mu;
using namespace Net;

Socket::~Socket()
{
    sockets::close(sockfd_);
}

void Socket::bindAddress(const InetAddress &localAddress) {
    sockets::bindOrDie(sockfd_, localAddress.getAddress());
}

void Socket::listen()
{
    sockets::listenOrDie(sockfd_);
}

int Socket::accept(InetAddress &peerAddress) {
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    int connfd = sockets::accept(sockfd_, &addr);

    if(connfd >= 0)
    {
        peerAddress.setAddress(addr);
    }
    return connfd;
}

void Socket::shutDownWrite() {
    sockets::shutDownWrite(sockfd_);
}

void Socket::setReuseAddress(bool on)
{
    int opt = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
}
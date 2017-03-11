//
// Created by jackson on 17-3-3.
//

#include <zconf.h>
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>
#include "Socketopts.h"


using namespace Mu;
using namespace Net;

int sockets::createNotBlockAndCloseOnExecOrDie() {
    int sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if(sockfd < 0)
    {
       // LOG_SYSFATAL << "sockets::createNotBlockAndCloseOnExecOrDie error";
    }
    return sockfd;
}

void sockets::setNotBlockAndCloseOnExec(int fd)
{
    int opt;
    //设置套接字为非阻塞
    opt = ::fcntl(fd, F_GETFL, 0);
    opt |= O_NONBLOCK;
    ::fcntl(fd, F_SETFL, opt);
    //设置套接字为exec后关闭
    opt = ::fcntl(fd, F_GETFL, 0);
    opt |= O_CLOEXEC;
    ::fcntl(fd, F_SETFL, opt);
}

void sockets::close(int fd) {
    if(::close(fd) < 0)
    {
       // LOG_SYSFATAL << "sockets::close error";
    }
}

void sockets::bindOrDie(int fd, const struct sockaddr_in &addr) {
    if(::bind(fd, sockAddrCast(&addr), sizeof(addr)) < 0)
    {
       // LOG_SYSFATAL << "sockets::bindOrDie error";

    }
}

void sockets::listenOrDie(int fd) {
    if(::listen(fd, SOMAXCONN) < 0)
    {
      //  LOG_SYSFATAL << "sockets::listenOrDie error";
    }
}

int sockets::accept(int fd, struct sockaddr_in *peerAddress) {
    socklen_t addrLen = sizeof(*peerAddress);
    int connfd = ::accept(fd, sockAddrCast(peerAddress), &addrLen);
    setNonBlockAndCloseOnExec(connfd);

    if(connfd < 0)
    {
        int savedErrno = errno;
       // LOG_SYSERR << "Socket::accept";
        switch (savedErrno)
        {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO: // ???
            case EPERM:
            case EMFILE: // per-process lmit of open file desctiptor ???
                // expected errors
                errno = savedErrno;
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
                // unexpected errors
            //    LOG_FATAL << "unexpected error of ::accept " << savedErrno;
                break;
            default:
             //   LOG_FATAL << "unknown error of ::accept " << savedErrno;
                break;
        }
    }
    return connfd;
}

void sockets::shutDownWrite(int fd) {
    if(::shutdown(fd, SHUT_WR) < 0)
    {
      //  LOG_SYSERR << "sockets::shutDownWrite error";
    }
}

const struct sockaddr * sockets::sockAddrCast(const struct sockaddr_in *addr) const {
    return static_cast<const struct sockaddr *>(addr);
}

struct sockaddr * sockets::sockAddrCast(struct sockaddr_in *addr) {
    return static_cast<struct sockaddr *>(addr);
}
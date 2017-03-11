//
// Created by jackson on 17-3-3.
//

#ifndef SIMPLENETWORDLIBRARY_INETADDRESS_H
#define SIMPLENETWORDLIBRARY_INETADDRESS_H

#include <cstdint>
#include <netinet/in.h>

namespace Mu
{
namespace Net
{
    class InetAddress
    {
    public:
        explicit InetAddress(uint16_t port);
        InetAddress(const struct sockaddr_in &addr) : addr_(addr) {}
        //禁止复制
        InetAddress(const InetAddress &) = delete;

        struct sockaddr_in getAddress(){
            return addr_;
        }
        const struct sockaddr_in getAddress() const
        {
            return addr_;
        }
        void setAddress(const struct sockaddr_in &addr)
        {
            addr_ = addr;
        }
    private:
        struct sockaddr_in addr_;
    };
}
}


#endif //SIMPLENETWORDLIBRARY_INETADDRESS_H

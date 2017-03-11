//
// Created by jackson on 17-3-3.
//


#include <string.h>
#include "InetAddress.h"
#include "Endian.h"

using namespace Mu;
using namespace Net;

InetAddress::InetAddress(uint16_t port) {
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = sockets::hostToNetwork16(port);
    addr_.sin_addr.s_addr = sockets::hostToNetwork32(INADDR_ANY);
}
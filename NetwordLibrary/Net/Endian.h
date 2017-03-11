//
// Created by jackson on 17-3-4.
//

#include <stdint-gcc.h>
#include <endian.h>

#ifndef SIMPLENETWORDLIBRARY_ENDIAN_H
#define SIMPLENETWORDLIBRARY_ENDIAN_H

#endif //SIMPLENETWORDLIBRARY_ENDIAN_H

namespace Mu
{
namespace Net
{
    namespace sockets
    {
        inline uint64_t hostToNetwork64(uint64_t  host64)
        {
            return htobe16(host64);
        }
        inline uint32_t hostToNetwork32(uint32_t host32)
        {
            return htobe32(host32);
        }
        inline uint16_t hostToNetwork16(uint16_t host16)
        {
            return htobe16(host16);
        }
        inline uint64_t network64ToHost(uint64_t host64)
        {
            return be64toh(host64);
        }
        inline uint32_t network32ToHost(uint32_t host32)
        {
            return be32toh(host32);
        }
        inline uint16_t network16ToHost(uint16_t host16)
        {
            return be16toh(host16);
        }
    }
}
}
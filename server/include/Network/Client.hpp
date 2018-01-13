//
// Created by zgore on 10/01/18.
//

#ifndef RTYPE_CLIENT_HPP
#define RTYPE_CLIENT_HPP

#include <string>
#include <cstdint>

namespace Net
{
    struct              Client
    {
        uint16_t        port;
        std::string     ip;
    };
}


#endif //RTYPE_CLIENT_HPP

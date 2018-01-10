//
// Created by mymy on 09/01/18.
//

#ifndef RTYPE_PACKET_HPP
#define RTYPE_PACKET_HPP

namespace Net
{
    struct  Packet
    {
        unsigned int    clientId;
        unsigned short  code;
        void            *data;
    };
}


#endif //RTYPE_PACKET_HPP

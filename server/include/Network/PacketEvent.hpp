//
// Created by mymy on 09/01/18.
//

#ifndef RTYPE_PACKETEVENT_HPP
#define RTYPE_PACKETEVENT_HPP

namespace Net
{
    struct  PacketEvent
    {
        // add bool critic;
        unsigned int    clientId;
        unsigned short  code;
        void            *data;
    };
}


#endif //RTYPE_PACKET_HPP

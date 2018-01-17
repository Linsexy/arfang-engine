//
// Created by mymy on 09/01/18.
//

#ifndef RTYPE_PACKETEVENT_HPP
#define RTYPE_PACKETEVENT_HPP

namespace Net
{

    struct  PacketEvent
    {
        unsigned int    clientId;
        unsigned short  code;
        // 'critical' describe if the request must be resend if not received or not.
        bool            critical;
        int8_t          *data;
    };
}

#endif //RTYPE_PACKET_HPP

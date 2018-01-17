//
// Created by mymy on 09/01/18.
//

#ifndef RTYPE_CONNECTEVENT_HPP
#define RTYPE_CONNECTEVENT_HPP

#include <string>
#include "Protocol/Events/IEvent.hpp"

namespace Proto
{
    struct CConnectEvent : public IEvent
    {
        std::string pseudo;
    };

    struct CLeaveGameEvent : public IEvent
    {

    };

    struct CDisconnectEvent : public IEvent
    {

    };

    struct CControlEvent : public IEvent
    {
        enum    Control : short
        {
            UNKNOWN = -1,
            UP = 0,
            DOWN,
            LEFT,
            RIGHT,
            SHOOT
        };
        Control     action;
        std::string data;
    };

    struct SGUpdateWaitingGameEvent : public IEvent
    {
        unsigned char remainingTime;
    };

    struct SGStartGameEvent : public IEvent
    {
        unsigned int id;
    };

    struct SGUpdateGamePlayersEvent : public IEvent
    {
        enum State : short
        {
            DEAD,
            ALIVE,
            DISCONNECTED
        };
        unsigned int    playerId;
        std::string     pseudo;
        State           state;
    };

    struct SGLoadObjectEvent : public IEvent
    {
        unsigned int    id;
        std::string     dll;
    };

    struct SGUpdateObjectComponentsEvent : public IEvent
    {
        struct  Position {
            int x;
            int y;
        };

        enum    State : short {
            // Je sé po kwa mettre lo
        };

        unsigned int    id;
        Position        position;
        State           state;
        unsigned int    remainingLife;
        unsigned int    maxLife;
    };

    struct SGEndGameEvent : public IEvent {};

}




#endif //RTYPE_CONNECTEVENT_HPP

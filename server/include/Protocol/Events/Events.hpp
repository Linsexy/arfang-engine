//
// Created by mymy on 09/01/18.
//

#ifndef RTYPE_CONNECTEVENT_HPP
#define RTYPE_CONNECTEVENT_HPP

#include <string>
#include "Protocol/Events/IEvent.hpp"

namespace Proto
{
    struct ConnectEvent : public IEvent
    {
        std::string pseudo;
    };

    struct CreateGameEvent : public IEvent
    {
        std::string gameName;
    };

    struct JoinGameEvent : public IEvent
    {
        unsigned int idGame;
    };

    struct GetGameListEvent : public IEvent
    {
        unsigned int fromIdGame;
        unsigned int nbGames;
    };

    struct LeaveGameEvent : public IEvent
    {

    };

    struct DisconnectEvent : public IEvent
    {

    };


}




#endif //RTYPE_CONNECTEVENT_HPP

//
// Created by mymy on 09/01/18.
//

#ifndef RTYPE_PROTOCOLSYSTEM_HPP
#define RTYPE_PROTOCOLSYSTEM_HPP

#include <utils/Module.hpp>
#include <Network/Packet.hpp>

namespace Proto
{
    class ProtocolSystem : public utils::Module<ProtocolSystem, Net::Packet>
    {
    public:
        ProtocolSystem(Sex::Mediator *m) : utils::Module<ProtocolSystem, Net::Packet>(m) {};
        ~ProtocolSystem() = default;
        void handle(Net::Packet const &);

    private:
        void createConnectEvent(unsigned int, void *);
        void createCreateGameEvent(unsigned int, void *);
        void createLeaveGameEvent(unsigned int);
        void createDisconnectEvent(unsigned int);
        void createJoinGameEvent(unsigned int, void *);
        void createGetGameListEvent(unsigned int, void *);

    };
}



#endif //RTYPE_PROTOCOLSYSTEM_HPP

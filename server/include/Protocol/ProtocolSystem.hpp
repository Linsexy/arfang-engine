//
// Created by mymy on 09/01/18.
//

#ifndef RTYPE_PROTOCOLSYSTEM_HPP
#define RTYPE_PROTOCOLSYSTEM_HPP

#include <ecs/Module.hpp>
#include <Network/PacketEvent.hpp>

namespace Proto
{
    class ProtocolSystem : public Sex::Module<ProtocolSystem, Net::PacketEvent>
    {
    public:
        ProtocolSystem(Sex::Mediator *m) : Sex::Module<ProtocolSystem, Net::PacketEvent>(m) {};
        ~ProtocolSystem() = default;
        void handle(Net::PacketEvent const &);

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

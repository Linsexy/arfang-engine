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
    private:
        std::vector<unsigned int>   _connectedClients;

        // Client to game server
        void createCConnectGameEvent(Net::PacketEvent const&);
        void createCLeaveGameEvent(Net::PacketEvent const&);
        void createCDisconnectEvent(Net::PacketEvent const&);
        void createCControl(Net::PacketEvent const&);

        void sendResponse(unsigned int, unsigned short, Net::ReturnCode);
        bool clientIsConnected(unsigned int);
        bool removeClient(unsigned int);

    public:
        ProtocolSystem(std::shared_ptr<Sex::Mediator> m) : Sex::Module<ProtocolSystem, Net::PacketEvent>(m) {};
        ~ProtocolSystem() = default;
        void handle(Net::PacketEvent const &);
    };
}



#endif //RTYPE_PROTOCOLSYSTEM_HPP

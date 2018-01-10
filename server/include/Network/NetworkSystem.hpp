//
// Created by zgore on 09/01/18.
//

#ifndef RTYPE_NETWORKSYSTEM_HPP
#define RTYPE_NETWORKSYSTEM_HPP

#include <utils/Module.hpp>
#include <thread>
#include <queue>
#include <mutex>
#include "Packet.hpp"
#include "SocketUDP.hpp"

namespace Net
{
    class       NetworkSystem : public utils::Module<NetworkSystem, Net::Packet>
    {
    private:
        std::unique_ptr<Net::ISocket>   _socket;
        std::thread                     _thread;
        std::mutex                      _packetsMutex;
        std::queue<Net::Packet>         _packetsReceived;
        std::queue<Net::Packet>         _packetsToSend;

        // Loop condition in the threaded ProcessPacket method
        bool                            _process;

    public:
        NetworkSystem(Sex::Mediator *m) : utils::Module<NetworkSystem, Net::Packet>(m),
                                           _socket(new SocketUDP(4242)),
                                           _thread(&NetworkSystem::ProcessPacket, this),
                                           _process(true) {}

        ~NetworkSystem()
        {
            _process = false;
            _thread.join();
        }

        void    handle(Net::Packet const &packet);
        void    ProcessPacket();
        void    update() override;

    };
}

#endif //RTYPE_NETWORKSYSTEM_HPP

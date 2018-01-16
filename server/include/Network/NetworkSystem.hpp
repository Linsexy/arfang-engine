//
// Created by zgore on 09/01/18.
//

#ifndef RTYPE_NETWORKSYSTEM_HPP
#define RTYPE_NETWORKSYSTEM_HPP

#include <ecs/Module.hpp>
#include <thread>
#include <queue>
#include <mutex>
#include <algorithm>
#include "PacketEvent.hpp"
#include "SocketUDP.hpp"
#include "Client.hpp"

// TODO : Not transit PacketEvent between systems, just the data. Protocol must cast it itself.
namespace Net
{
	class       NetworkSystem : public Sex::Module<NetworkSystem, Net::PacketEvent>
	{
	private:
		unsigned int                        _lastClientID;
		std::unique_ptr<Net::ASocketUDP>    _socket;
		std::thread                         _thread;
		std::mutex                          _packetsMutex;
		std::queue<Net::PacketEvent>        _packetsReceived;
		std::queue<Net::PacketEvent>        _packetsToSend;
		std::unordered_map<unsigned int, Net::Client>            _clients;

		// Loop condition in the threaded ProcessPacket method
		bool                                _process;

	public:
		NetworkSystem(std::shared_ptr<Sex::Mediator> const &m)
				: Sex::Module<NetworkSystem, Net::PacketEvent>(m, "NetworkSystem"),
										  _lastClientID(0),
										  _socket(new SocketUDP(4242)),
										  _thread(&NetworkSystem::ProcessPacket, this),
										  _process(true) {}

		~NetworkSystem()
		{
			_process = false;
			_thread.join();
		}

		bool            clientExisting(Client const&);
		unsigned int    createClient(Client const&);
		unsigned int    getClientId(Client const&);
		void            handle(Net::PacketEvent const &);
		void            ProcessPacket();
		void            update() override;
		ssize_t         sendMsgByID(size_t, const void *, size_t);
	};
}

#endif //RTYPE_NETWORKSYSTEM_HPP

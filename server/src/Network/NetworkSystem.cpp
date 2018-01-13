//
// Created by zgore on 09/01/18.
//

#include <cstring>
#include "Packet.hpp"
#include "Network/NetworkSystem.hpp"

void        Net::NetworkSystem::ProcessPacket()
{
    ssize_t     bytesRead;

    while (this->_process)
    {
        // TODO: Test bytesReads length
        bytesRead = _socket->recvData(sizeof(Net::Packet));

        _packetsMutex.lock();
        if (_socket->hasPendingData())
        {
            Client              client;
            PacketEvent         receivedPacket;
            Net::Packet         *tmp;

            //TODO: Segfault with CLION, possibly double free and problem with shared ptr
            auto data = _socket->getPendingData(client.ip, client.port);

            receivedPacket.clientId = getClientId(client);

            tmp = reinterpret_cast<Net::Packet *>(data.get());
            receivedPacket.code = tmp->actionType;
            //std::memcpy(&receivedPacket.data, &data, sizeof(data));

            // TODO: Use RequestID for packet lost
            // -> tmp.requestId

            // TODO: push in _packetReceived the created packet
            _packetsReceived.push(receivedPacket);
        }
        _packetsMutex.unlock();

        _packetsMutex.lock();
        // TODO: pop packet from _packetToSend

        if (!_packetsToSend.empty())
        {
            auto sendingPacket = _packetsToSend.front();
            _packetsToSend.pop();
            sendMsgByID(sendingPacket.clientId, sendingPacket.data, sizeof(sendingPacket));
        }
        _packetsMutex.unlock();

        // send a packet
    }
}

unsigned int Net::NetworkSystem::createClient(Client const& client) {
    Client newClient(client);

    _clients[++_lastClientID] = newClient;
    return (_lastClientID);
}

unsigned int    Net::NetworkSystem::getClientId(Client const& client)
{
    auto found = std::find_if(_clients.begin(), _clients.end(),
                              [client](auto const &elem){
                                  return (elem.second.ip == client.ip) && (elem.second.port == client.port);
                              });
    if (found == _clients.end())
        return (createClient(client));
    return (found->first);
}


bool        Net::NetworkSystem::clientExisting(Client const& client)
{
    std::unordered_map<unsigned int, Net::Client>::iterator found = std::find_if(_clients.begin(), _clients.end(),
                                                                                 [client](auto const &elem){
                                                                                     return (elem.second.ip == client.ip) && (elem.second.port == client.port);
                                                                                 });
    return !(found == _clients.end());
}

ssize_t     Net::NetworkSystem::sendMsgByID(size_t id, const void *buffer, size_t length)
{
    try
    {
        auto const &client = _clients.at(id);
        return (_socket->sendMsg(client.ip, client.port, buffer, length));
    } catch (std::out_of_range &e) {
        throw Net::NetworkError("ID not found");
    }
}

void            Net::NetworkSystem::handle(Net::PacketEvent const &packet)
{
    std::lock_guard<std::mutex>     lock(_packetsMutex);

    std::cout << "PacketEvent handled for client n°" << packet.clientId << std::endl;
    _packetsToSend.push(packet);
}

void            Net::NetworkSystem::update()
{
    std::lock_guard<std::mutex>     lock(_packetsMutex);
    if (_packetsReceived.empty())
        return;
    auto event = _packetsReceived.front();
    _packetsReceived.pop();
    this->transmit(event);
};
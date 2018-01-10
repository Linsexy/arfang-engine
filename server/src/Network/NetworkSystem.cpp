//
// Created by zgore on 09/01/18.
//

#include "Network/NetworkSystem.hpp"

void        Net::NetworkSystem::ProcessPacket()
{
    int8_t      buffer[512]; // <=> char buffer[512] ?
    //ssize_t     bytesRead;

    while (this->_process)
    {
        // TODO: Test bytesReads length
        //bytesRead = _socket->recvMsg(buffer, 1024);
        //buffer[bytesRead] = '\0';
        _packetsMutex.lock();
        // TODO: push in _packetReceived the created packet
        _packetsMutex.unlock();
        std::cout << "Data received : " << buffer << std::endl;
        _packetsMutex.lock();
        // TODO: pop packet from _packetToSend
        _packetsMutex.unlock();
        //_socket->sendMsgByID(this->_socket_currentClient - 1, buffer, 10);
    }
}

void            Net::NetworkSystem::handle(Net::Packet const &packet)
{
    std::lock_guard<std::mutex>     lock(_packetsMutex);

    std::cout << "Packet handled for client n°" << packet.clientId << std::endl;
    _packetsToSend.push(packet);
}

void            Net::NetworkSystem::update()
{
    std::lock_guard<std::mutex>     lock(_packetsMutex);
    // TODO: Create an event to send it to the Protocol
    _packetsReceived.pop();
}
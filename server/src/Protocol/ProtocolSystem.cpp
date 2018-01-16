//
// Created by mymy on 09/01/18.
//

#include <cstring>
#include <ReturnCode.hpp>
#include "Protocol/ProtocolSystem.hpp"
#include "Protocol/ProtocolError.hpp"
#include "Protocol/Events/Events.hpp"
#include "ActionType.hpp"

void Proto::ProtocolSystem::handle(Net::PacketEvent const &packet)
{
    if (packet.code != Proto::ActionType::C_CONNECT_GAME && !this->clientIsConnected(packet.clientId))
    {
        this->sendResponse(packet.clientId, packet.code, Net::ReturnCode::NOT_AUTHORIZED);
        return ;
    }
    switch (packet.code)
    {
        case Proto::ActionType::C_CONNECT_GAME :
            this->createCConnectGameEvent(packet);
            break;
        case Proto::ActionType::C_LEAVE_GAME :
            this->createCLeaveGameEvent(packet);
            break;
        case Proto::ActionType::C_DISCONNECT :
            this->createCDisconnectEvent(packet);
            break;
        case Proto::ActionType::C_CONTROL :
            this->createCControl(packet);
            break;
        default:
            throw ProtocolError("Unknown code");
    }
    delete(packet.data);
}

void Proto::ProtocolSystem::sendResponse(unsigned int clientId, unsigned short code, Net::ReturnCode rstatus)
{
    Net::PacketEvent    resPacket;

    resPacket.clientId = clientId;
    resPacket.code = code;
    resPacket.critical = true;
    Net::ReturnCode *rstatusData = new(Net::ReturnCode);
    *rstatusData = rstatus;
    std::memcpy(&resPacket.data, rstatusData, sizeof(Net::ReturnCode));
    this->transmit(resPacket);
}

void Proto::ProtocolSystem::createCConnectGameEvent(Net::PacketEvent const& packet)
{
    CConnectEvent       event;


    event.clientId = packet.clientId;
    _connectedClients.push_back(packet.clientId);
    event.pseudo = std::string(reinterpret_cast<char *>(packet.data));
    this->transmit(event);
    this->sendResponse(packet.clientId, packet.code, Net::ReturnCode::OK);
}

void Proto::ProtocolSystem::createCLeaveGameEvent(Net::PacketEvent const& packet)
{
    CLeaveGameEvent event;

    event.clientId = packet.clientId;
    this->transmit(event);
    this->sendResponse(packet.clientId, packet.code, Net::ReturnCode::OK);
}

void Proto::ProtocolSystem::createCDisconnectEvent(Net::PacketEvent const& packet)
{
    CDisconnectEvent event;

    event.clientId = packet.clientId;
    this->removeClient(packet.clientId);
    this->transmit(event);
    this->sendResponse(packet.clientId, packet.code, Net::ReturnCode::OK);
}

void Proto::ProtocolSystem::createCControl(Net::PacketEvent const& packet)
{
    CControlEvent   event;

    event.clientId  = packet.clientId;
    event.action    = *reinterpret_cast<CControlEvent::Control *>(packet.data);
    event.data      = std::string(reinterpret_cast<char *>(&packet.data[sizeof(CControlEvent::Control)]));
    this->transmit(event);
    this->sendResponse(packet.clientId, packet.code, Net::ReturnCode::OK);
}

bool Proto::ProtocolSystem::clientIsConnected(unsigned int clientId)
{
    auto found = std::find_if(_connectedClients.begin(), _connectedClients.end(),
                              [clientId](auto const &elem){
                                  return (elem == clientId);
                              });
    return (found == _connectedClients.end());
}

bool Proto::ProtocolSystem::removeClient(unsigned int clientId)
{
    auto found = std::find_if(_connectedClients.begin(), _connectedClients.end(),
                              [clientId](auto const &elem){
                                  return (elem == clientId);
                              });
    if (found == _connectedClients.end())
        return false;
    _connectedClients.erase(found);
    return true;
}
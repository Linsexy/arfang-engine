//
// Created by mymy on 09/01/18.
//

#include "Protocol/ProtocolSystem.hpp"
#include "Protocol/ProtocolError.hpp"
#include "Protocol/Events/Events.hpp"
#include "ActionType.hpp"

void Proto::ProtocolSystem::handle(Net::PacketEvent const &packet)
{
    switch (packet.code)
    {
        case Proto::ActionType::CONNECT :
            this->createConnectEvent(packet.clientId, packet.data);
            break;
        case Proto::ActionType::CONTROL :
            break;
        case Proto::ActionType::CREATE_GAME :
            this->createCreateGameEvent(packet.clientId, packet.data);
            break;
        case Proto::ActionType::DISCONNECT :
            this->createDisconnectEvent(packet.clientId);
            break;
        case Proto::ActionType::GET_GAME_LIST :
            this->createGetGameListEvent(packet.clientId, packet.data);
            break;
        case Proto::ActionType::JOIN_GAME :
            this->createJoinGameEvent(packet.clientId, packet.data);
            break;
        case Proto::ActionType::LEAVE_GAME :
            this->createLeaveGameEvent(packet.clientId);
            break;
        default:
            throw ProtocolError("Unknown code");
    }
}

void Proto::ProtocolSystem::createConnectEvent(unsigned int clientId, void *data)
{
    ConnectEvent event;

    event.clientId = clientId;
    event.pseudo = std::string(static_cast<char *>(data));
    this->transmit(event);
}

void Proto::ProtocolSystem::createCreateGameEvent(unsigned int clientId, void *data)
{
    CreateGameEvent event;

    event.clientId = clientId;
    event.gameName = std::string(static_cast<char *>(data));
    this->transmit(event);
}

void Proto::ProtocolSystem::createLeaveGameEvent(unsigned int clientId)
{
    LeaveGameEvent event;

    event.clientId = clientId;
    this->transmit(event);
}

void Proto::ProtocolSystem::createDisconnectEvent(unsigned int clientId)
{
    DisconnectEvent event;

    event.clientId = clientId;
    this->transmit(event);
}

void Proto::ProtocolSystem::createJoinGameEvent(unsigned int clientId, void *data)
{
    JoinGameEvent event;

    event.clientId = clientId;
    event.idGame = *(static_cast<unsigned int *>(data));
    this->transmit(event);
}

void Proto::ProtocolSystem::createGetGameListEvent(unsigned int clientId, void *data)
{
    GetGameListEvent event;

    event.clientId = clientId;
    event.fromIdGame = *(static_cast<unsigned int *>(data));
    event.nbGames = *(reinterpret_cast<unsigned int *>(static_cast<unsigned char *>(data) + sizeof(unsigned int)));
    this->transmit(event);
}
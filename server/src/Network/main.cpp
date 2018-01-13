
#include "Network/SocketUDP.hpp"
#include "Network/NetworkSystem.hpp"
#include "ecs/Mediator.hpp"

// Test main for SocketUDP
int         main(void)
{
    Sex::Mediator mediator;
    Net::NetworkSystem networkSystem(&mediator);

    networkSystem.ProcessPacket();
    return (0);
}
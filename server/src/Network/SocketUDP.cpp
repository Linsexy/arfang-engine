/*
** SocketUDP.cpp for rtype in /home/quaresc/CLionProjects/rtype/SocketUDP.cpp
**
** Made by Clement Quaresma
** Login   <clement.quaresma@epitech.eu>
**
** Started on  lun. janv. 08 14:33:06 2018 Clement Quaresma
** Last update lun. janv. 08 14:33:06 2018 Clement Quaresma
*/

// TODO: ifdef window à mettre dans le system
#ifdef WIN32

#include <winsock2.h>

#else

#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>
#include <iostream>

#endif

#include "Network/SocketUDP.hpp"

Net::SocketUDP::SocketUDP(uint16_t const &port)
{
#ifdef WIN32
    WSADATA wsa;
        int err = WSAStartup(MAKEWORD(2, 2), &wsa);
        if (err < 0)
	    throw Net::NetworkError("WSAStartup failed !");
#endif
    _port = port;
    _fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_fd == -1)
        throw Net::NetworkError(std::strerror(errno));
    std::cout << "Socket opened on port " << _port << std::endl;
    this->bindSocket("", _port);
}

Net::SocketUDP::~SocketUDP()
{
    close(_fd);
#ifdef WIN32
    WSACleanup();
#endif
}

void        Net::SocketUDP::bindSocket(std::string const &, uint16_t port)
{
    struct sockaddr_in sin;

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    if (bind(_fd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
        throw Net::NetworkError(std::strerror(errno));
}

ssize_t     Net::SocketUDP::recvMsg(void *buffer, size_t length)
{
    ssize_t            receivedBytes;
    struct sockaddr_in from;
    int                fromlen;

    fromlen = sizeof(from);
    if ((receivedBytes = recvfrom(_fd, buffer, length, 0, (struct sockaddr *)&from, (socklen_t *)&fromlen)) == -1)
        throw Net::NetworkError(std::strerror(errno));

    Client  client;
    client.ip   = std::string(inet_ntoa(from.sin_addr));
    client.port = ntohs(from.sin_port);
    _pendingData.push(std::make_pair(client, std::shared_ptr<int8_t>(static_cast<int8_t *>(buffer))));

    return (receivedBytes);
}

ssize_t     Net::SocketUDP::sendMsg(std::string const &ip, uint16_t port, const void *buffer, size_t length)
{
    ssize_t sentBytes;
    struct sockaddr_in sin;

    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    if ((sentBytes = sendto(_fd, buffer, length, 0, (struct sockaddr *)&sin, sizeof(sin))) == -1)
        throw Net::NetworkError(std::strerror(errno));
    return (sentBytes);
}
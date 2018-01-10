/*
** SocketUDP.hpp for rtype in /home/quaresc/CLionProjects/rtype/SocketUDP.hpp
**
** Made by Clement Quaresma
** Login   <clement.quaresma@epitech.eu>
**
** Started on  lun. janv. 08 14:24:27 2018 Clement Quaresma
** Last update lun. janv. 08 14:24:27 2018 Clement Quaresma
*/

#ifndef RTYPE_SOCKETUDP_HPP
#define RTYPE_SOCKETUDP_HPP

#include <map>
#include <netinet/in.h>
#include <sys/socket.h>
#include <utility>
#include "ISocket.hpp"
#include "NetworkError.hpp"

namespace Net
{
    class SocketUDP : public ISocket
    {
    private:
        // TODO: Move this map in NetworkSystem ? Cause recons
        std::map<unsigned int, std::pair<std::string, uint16_t>> _clients;
        unsigned int  _currentClient;


     public:
        SocketUDP(uint16_t const &);
        ~SocketUDP();

        ssize_t		sendMsgByID(size_t, const void *, size_t);

     protected:
        ssize_t		sendMsg(std::string const &ip, uint16_t port, const void *, size_t);
        ssize_t		recvMsg(void *, size_t);
        void		bindSocket(std::string const &, uint16_t);
        void		connectSocket() {};
        void		listenSocket(size_t) {};
        int		    acceptSocket() { return 0; };
    };
}

#endif /* !RTYPE_SOCKETUDP_HPP */

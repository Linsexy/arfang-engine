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
#include "ASocketUDP.hpp"
#include "NetworkError.hpp"

namespace Net
{
    class SocketUDP : public ASocketUDP
    {
     public:
        SocketUDP(uint16_t const &);
        ~SocketUDP();


     protected:
        void		bindSocket(std::string const &, uint16_t);
        void		connectSocket() {};
        void		listenSocket(size_t) {};
        int		    acceptSocket() { return 0; };
        ssize_t     recvMsg(void *, size_t);
        ssize_t     sendMsg(std::string const &, uint16_t, const void *, size_t);

    };
}

#endif /* !RTYPE_SOCKETUDP_HPP */

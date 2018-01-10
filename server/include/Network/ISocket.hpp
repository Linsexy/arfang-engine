/*
** ISocket.hpp for rtype in /home/quaresc/CLionProjects/rtype/ISocket.hpp
**
** Made by Clement Quaresma
** Login   <clement.quaresma@epitech.eu>
**
** Started on  lun. janv. 08 14:25:10 2018 Clement Quaresma
** Last update lun. janv. 08 14:25:10 2018 Clement Quaresma
*/
#ifndef RTYPE_ISOCKET_HPP
#define RTYPE_ISOCKET_HPP

#include <string>

namespace Net
{
    class ISocket
    {
    protected:
        int         _fd;
        uint16_t    _port;

    public:
        ISocket() = default;
        virtual ~ISocket() = default;


    protected:
        virtual ssize_t	    sendMsg(std::string const &, uint16_t, const void *, size_t) = 0;
        virtual ssize_t	    recvMsg(void *, size_t) = 0;
        virtual void		bindSocket(std::string const &, uint16_t) = 0;
        virtual void		connectSocket() = 0;
        virtual void		listenSocket(size_t) = 0;
        virtual int		    acceptSocket() = 0;
    };
}

#endif /* !RTYPE_ISOCKET_HPP */

//
// Created by zgore on 10/01/18.
//

#ifndef RTYPE_ASOCKETUDP_HPP
#define RTYPE_ASOCKETUDP_HPP

#include <queue>
#include <memory>
#include "ISocket.hpp"
#include "Client.hpp"

namespace   Net
{
    class   ASocketUDP : public ISocket
    {
    protected:
        std::queue<std::pair<Net::Client, std::shared_ptr<int8_t>>>     _pendingData;
    public:
        virtual ssize_t	    sendMsg(std::string const &, uint16_t, const void *, size_t) = 0;

        bool                hasPendingData() const
        {
            return (!_pendingData.empty());
        }

        std::shared_ptr<int8_t>        getPendingData(std::string &ip, uint16_t &port)
        {
            auto data = _pendingData.front();
            ip = data.first.ip;
            port = data.first.port;
            _pendingData.pop();
            return (data.second);
        }

        ssize_t                         recvData(size_t length)
        {
            void    *buffer = new int8_t[length];
            return (this->recvMsg(buffer, length));
        }
    };
}

#endif //RTYPE_ASOCKETUDP_HPP

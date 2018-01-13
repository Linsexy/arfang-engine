//
// Created by mymy on 09/01/18.
//

#ifndef RTYPE_PROTOCOLERROR_HPP
#define RTYPE_PROTOCOLERROR_HPP

#include <string>
#include <exception>

class ProtocolError : public std::exception
{
    std::string _msg;

public:
    ProtocolError(std::string const &msg) :
    _msg(msg) {};
    ~ProtocolError() throw() {};

    const char *what() const throw() override
    {
        return (this->_msg.c_str());
    }
};

#endif //RTYPE_PROTOCOLERROR_HPP

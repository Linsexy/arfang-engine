/*
** NetworkError.hpp for rtype in /home/quaresc/CLionProjects/rtype/NetworkError.hpp
**
** Made by Clement Quaresma
** Login   <clement.quaresma@epitech.eu>
**
** Started on  lun. janv. 08 14:41:57 2018 Clement Quaresma
** Last update lun. janv. 08 14:41:57 2018 Clement Quaresma
*/
#ifndef RTYPE_NETWORKERROR_HPP
#define RTYPE_NETWORKERROR_HPP

#include <string>

namespace Net
{
    class NetworkError : public std::exception
    {
      std::string _msg;

     public:
      NetworkError(std::string const &msg) :
	      _msg(msg) {};
      ~NetworkError() throw() {};

      const char *what() const throw() override
      {
	return (this->_msg.c_str());
      }
    };
}
#endif /* !RTYPE_NETWORKERROR_HPP */

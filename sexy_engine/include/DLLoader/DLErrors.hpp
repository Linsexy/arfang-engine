//
// Created by mymy on 04/01/18.
//

#ifndef RTYPE_DLERRORS_HPP
#define RTYPE_DLERRORS_HPP

#include <exception>
#include <string>

namespace Sex
{
    class DLErrors : public std::exception
    {
        std::string _msg;

        public:
            DLErrors(std::string const &msg) :
                    _msg(msg) {};
            ~DLErrors() throw() {};

            const char *what() const throw() override
            {
                return (this->_msg.c_str());
            }
    };
}

#endif //RTYPE_DLERRORS_HPP

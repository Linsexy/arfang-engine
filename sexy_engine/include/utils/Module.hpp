//
// Created by benito on 1/8/18.
//

#ifndef RTYPE_MODULE_HPP
#define RTYPE_MODULE_HPP

#include "IndexType.hpp"

namespace utils
{

    /* If A inherits from Module, CRTP must be A */
    template<typename CRTP, typename... Events>
    class Module
    {
        template<typename T>
        void handle(const T &arg) const {
            static_cast<CRTP *>(this)->handle(arg);
        }

        auto getTypes() const noexcept {
            return (IndexType::getMany<Events...>());
        }
    };
}

#endif //RTYPE_MODULE_HPP

//
// Created by benito on 1/8/18.
//

#ifndef RTYPE_MODULE_HPP
#define RTYPE_MODULE_HPP

#include "IndexType.hpp"
#include "ecs/Mediator.hpp"

namespace utils
{

    /* If A inherits from Module, CRTP must be A */
    template<typename CRTP, typename... Events>
    class Module
    {
    public:
        template<typename T>
        void handle(const T &arg) {
            static_cast<CRTP *>(this)->handle(arg);
        }

        auto getTypes() const noexcept {
            return (IndexType::getMany<Events...>());
        }

    private:
        template <typename T, typename M>
        void doTransmit(const T& toTransmit, M *med)
        {
            med->transmit(static_cast<CRTP *>(this), toTransmit);
        };

    public:
        template <typename T, typename Med = Sex::Mediator>
        void transmit(const T& t)
        {
            doTransmit(t, static_cast<CRTP *>(this)->getMediator());
        }
    };
}

#endif //RTYPE_MODULE_HPP

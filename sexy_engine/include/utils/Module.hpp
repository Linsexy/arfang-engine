//
// Created by benito on 1/8/18.
//

#ifndef RTYPE_MODULE_HPP
#define RTYPE_MODULE_HPP

#include <ecs/ASystem.hpp>
#include "IndexType.hpp"

namespace utils
{

    /* If A inherits from Module, CRTP must be A */
    template<typename CRTP, typename... Events>
    class Module : public Sex::ASystem
    {
    public:

        template <typename Med>
        Module(Med *m) : ASystem(m)
        {
            {(addHandler<Events>())...};
        }

        template <typename DT>
        void addHandler() {
            auto id = utils::IndexType::get<DT>();
            this->_fptr.emplace(id,
                                [this](const AbstractData &abstractData) {
                                    std::cout << "I'm an handler" << std::endl;
                                    auto toSend = static_cast<const ConcreteData <DT> &>(abstractData);
                                    static_cast<CRTP *>(this)->handle(toSend.data);
                                });
        }

        virtual ~Module() = default;

        virtual void handler(const AbstractData& data) override
        {
            std::cout << "still receiving" << std::endl;
            auto ret = _fptr.find(data.mType);
            std::cout << data.mType << std::endl;
            for (auto a : _fptr)
            {
                std::cout << "-> " << a.first << std::endl;
            }
            if (ret != _fptr.end())
            {
                std::cout << "found someone" << std::endl;
                ret->second(data);
            }
        }

        auto getTypes() const noexcept {
            return (IndexType::getMany<Events...>());
        }

    public:
        template <typename T>
        void transmit(const T& t)
        {
            std::cout << "Transmitting" << std::endl;
            static_cast<CRTP *>(this)->getMediator()->transmit(static_cast<CRTP *>(this), t);
        }

    private:
        std::unordered_map<unsigned int, std::function<void(const AbstractData&)> > _fptr;
    };
}

#endif //RTYPE_MODULE_HPP

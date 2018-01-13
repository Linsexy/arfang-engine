//
// Created by benito on 1/8/18.
//

#ifndef RTYPE_MODULE_HPP
#define RTYPE_MODULE_HPP

#include <unordered_map>
#include "ecs/ASystem.hpp"
#include "utils/IndexType.hpp"
#include "GameObject.hpp"
#include "Mediator.hpp"

namespace Sex
{

    /* If A inherits from Module, CRTP must be A */
    template<typename CRTP, typename... Events>
    class Module : public ASystem
    {
    public:

        template <typename Med>
        Module(Med *m) : ASystem(m)
        {
            static_assert(std::is_base_of<Module, CRTP>::value,
            "If a System X inherits from Module, it must template it on itself (class X : public Module<X>)");
            (addHandler<Events>(),...);
        }

        virtual ~Module() = default;

    private:
        template <typename DT>
        void addHandler() {
            auto id = utils::IndexType::get<DT>();
            this->_fptr.emplace(id,
                                [this](const AbstractData &abstractData) {
                                    //std::cout << "I'm an handler" << std::endl;
                                    auto toSend = static_cast<const ConcreteData <DT> &>(abstractData);
                                    static_cast<CRTP *>(this)->handle(toSend.data);
                                });
        }

    public:
        template <typename ET, typename... Args>
        std::shared_ptr<ET> createObject(const Args&... args) const
        {
            static_assert(std::is_base_of<GameObject, ET>::value,
                          "This function aims creating GameObjects, not your shit");
            auto ret = std::make_shared<ET>(args...);
            transmit(ret);
            return (ret);
        }

    protected:
        virtual void handler(const AbstractData& data) override
        {
            auto ret = _fptr.find(data.mType);
            if (ret != _fptr.end())
            {
                //std::cout << "found someone" << std::endl;
                ret->second(data);
            }
        }

    public:
        auto getTypes() const noexcept {
            return (utils::IndexType::getMany<Events...>());
        }

        template <typename T>
        void transmit(const T& t) const
        {
            //std::cout << "Transmitting" << std::endl;
            mediator->transmit(static_cast<const CRTP *>(this), t);
        }

    private:
        std::unordered_map<unsigned int,
    						std::function <void(const AbstractData&)> > _fptr;
    };
}

#endif //RTYPE_MODULE_HPP

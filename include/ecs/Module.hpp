//
// Created by benito on 1/8/18.
//

#ifndef RTYPE_MODULE_HPP
#define RTYPE_MODULE_HPP

#include <unordered_map>
//#include <utils/Named.hpp>
#include "utils/IndexType.hpp"
#include "ecs/ASystem.hpp"
#include "GameObject.hpp"

namespace Af
{

    /* If A inherits from Module, CRTP must be A */
    template<typename CRTP, typename... Events>
    class Module : public ASystem/*, public utils::Named<CRTP>*/
    {
    public:

        template<typename Med>
        Module(const std::shared_ptr<Med> &m = nullptr/*, const std::string &className = "NoClassName"*/)
                : ASystem(m)/*, utils::Named<CRTP>(className)*/
        {
            static_assert(std::is_base_of<Module, CRTP>::value,
                          "If a System X inherits from Module, it must template it on itself (class X : public Module<X>)");


            (addHandler<Events>(),...);
        }

        virtual ~Module() = default;

    public:

        template<typename ET, typename... Args>
        std::shared_ptr<ET> createObject(Args &&... args) const
        {
            static_assert(std::is_base_of<GameObject, ET>::value,
                          "This function aims creating GameObjects, not this");

            auto ret = std::make_shared<ET>(std::forward<Args>(args)...);
            transmit(static_cast<const std::shared_ptr<GameObject> &>(ret));
            return (ret);
        }

        void destroyObject(std::shared_ptr<GameObject> &objectToDestroy) const
        {
            GameObject::DeleteEvent const deleteEvent = GameObject::DeleteEvent(objectToDestroy);
            transmit(deleteEvent);
            objectToDestroy.reset();
        }

        /* entities were ALWAYS allocated on the heap, it may be a behavior we do not want
        auto createObject(utils::IndexType::meta type) const
        {
            auto ret = EntityFactory::create(type);
            transmit(static_cast<const std::shared_ptr<GameObject> &>(ret));
            return (ret);
        }

        auto createObject(utils::IndexType::meta type, unsigned int id) const
        {
            auto ret = EntityFactory::create(type, id);
            transmit(static_cast<const std::shared_ptr<GameObject> &>(ret));
            return (ret);
        }
         */

        /*template<typename ST, typename... Args>
        auto addSubSystem(Args &&...args)
        {
            static_assert(std::is_base_of<ASystem, ST>::value,
                          "You should add Systems, not ponies");

            auto ret = std::make_shared<ST>(mediator, std::forward<Args>(args)...);
            mediator->addSystem(ret.get());
            _subS.emplace(utils::IndexType::get<ST>(), ret);
            return ret;
        }*/

        utils::IndexType::meta getIndexType() const noexcept override
        {
            return (utils::IndexType::get<CRTP>());
        }

        std::vector<utils::IndexType::meta> getTypes() const noexcept override
        {
            return (utils::IndexType::getMany<Events...>());
        }

        template<typename T>
        void transmit(const T &t) const
        {
            //std::cout << "Transmitting" << std::endl;
            mediator->transmit(static_cast<const CRTP *>(this), t);
        }

    protected:
        void handler(const AbstractData &data) override
        {
            auto ret = _fptr.find(data.mType);
            if (ret != _fptr.end())
            {
                //std::cout << "found someone" << std::endl;
                ret->second(data);
            }
        }

    private:
        template<typename EventType>
        void addHandler()
        {
            auto id = utils::IndexType::get<EventType>();
            this->_fptr.emplace(id,
                                [this](auto &&abstractData)
                                {
                                    //std::cout << "I'm an handler" << std::endl;
                                    auto toSend = static_cast<const ConcreteData <EventType> &>(abstractData);
                                    static_cast<CRTP *>(this)->handle(toSend.data);
                                });
        }

    private:
        std::unordered_map<utils::IndexType::meta,
                std::function<void( const AbstractData
        &)> >
        _fptr;
        //std::unordered_map<utils::IndexType::meta,
        //        std::shared_ptr<ASystem>> _subS;
    };
}

#endif //RTYPE_MODULE_HPP

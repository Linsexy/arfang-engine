//
// Created by benito on 1/8/18.
//

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

/* Core class of the engine */
#include <memory>
#include "Mediator.hpp"
#include "Module.hpp"

namespace Sex {
    struct Event
    {
        enum class Type
        {
            UNDEFINED,
            END_LOOP
        };

        Type t;
    };
    class Core : public Module<Core, Event> {
    private:
        std::unique_ptr<Mediator> mediator;
    public:

        Core() : mediator(std::make_unique<Mediator>()), isOver(false) {}
        ~Core() = default;


        template<typename ST, typename... Args>
        void emplaceSystem(Args &... args) {
            static_assert(std::is_base_of<ASystem, ST>::value,
                          "addSystem function should be called with a type inheriting from ASystem");

            auto s = std::make_shared<ST>(mediator.get(), args...);
            _systems.emplace(utils::IndexType::get<ST>(), s);
            mediator->addSystem(s.get());
        }

        template <typename ST>
        ST& getSystem()
        {
            auto& ptr= _systems.at(utils::IndexType::get<ST>());
            return (static_cast<ST&>(*ptr));
        }

        template <typename ST>
        const ST& getSystem() const
        {
            auto& ptr= _systems.at(utils::IndexType::get<ST>());
            return (static_cast<ST&>(*ptr));
        }

        Mediator *getMediator() const
        {
            return (mediator.get());
        }

        void go();

    private:
        bool isOver;
        std::unordered_map<unsigned int, std::shared_ptr<ASystem>> _systems;
    };
}

#endif //RTYPE_CORE_HPP

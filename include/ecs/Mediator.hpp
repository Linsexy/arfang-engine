//
// Created by benito on 1/4/18.
//

#ifndef ECS_MEDIATOR_HPP
#define ECS_MEDIATOR_HPP

#include <algorithm>
#include <unordered_map>
#include <utils/IndexType.hpp>
#include "ASystem.hpp"

//same func in Interface and Module

namespace Af {
    class Mediator/* : public BaseMediator<Mediator>*/ {
    public:
        Mediator() = default;
        ~Mediator() = default;

        /* TODO: note : c'est peut etre de la grosse merde que ST soit le type réel, faire attention. */
        template<typename ST, typename T>
        void transmit(const ST *sender, T&& transmit) {
            auto id = utils::IndexType::get<std::decay_t<T>>();
            for (const auto &sys : _systems) {
                if (sys.first != sender && std::find(sys.second.begin(), sys.second.end(), id) != sys.second.end()) {
                    sys.first->receive(transmit);
                }
            }
        }

        template <typename ST>
        void addSystem(ST *s)
        {
            _systems.emplace(s, s->getTypes());
        }

    private:
        std::unordered_map<ASystem *, std::vector<utils::IndexType::meta>> _systems;
    };
}

#endif //ECS_MEDIATOR_HPP

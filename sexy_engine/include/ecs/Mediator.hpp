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

namespace Sex {
    class Mediator/* : public BaseMediator<Mediator>*/ {
    public:
        Mediator() = default;
        ~Mediator() = default;

        template<typename ST, typename T>
        void transmit(const ST *sender, const T &transmit) {
             auto id = utils::IndexType::get<T>();
            for (const auto &sys : _systems) {
                /*for (auto x : sys.second)
                {
                    std::cout << x << std::endl;
                }*/
                std::cout << std::endl;
                if (sys.first != sender && std::find(sys.second.begin(), sys.second.end(), id) != sys.second.end()) {
                    //std::cout << "Jean Michel !" << std::endl;
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
        std::unordered_map<ASystem *, std::vector<unsigned int>> _systems;
    };
}

#endif //ECS_MEDIATOR_HPP

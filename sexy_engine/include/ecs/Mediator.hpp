//
// Created by benito on 1/4/18.
//

#ifndef ECS_MEDIATOR_HPP
#define ECS_MEDIATOR_HPP

#include <algorithm>
#include <unordered_map>
#include <utils/IndexType.hpp>

namespace Sex {
    class ASystem;
    class Mediator/* : public BaseMediator<Mediator>*/ {
    public:

        template<typename ST, typename T>
        void transmit(const ST *sender, const T &transmit) {
            auto id = utils::IndexType::get<T>();
            for (auto &sys : _systems) {
                ST *s = static_cast<ST *>(sys);
                auto v = s->getTypes();
                if (s != sender && std::find(v.begin(), v.end(), id) != v.end())
                    s->handle(transmit);
            }
        }

        void addSystem(ASystem *s)
        {
            _systems.push_back(s);
        }

    private:
        //std::unordered_map<unsigned int, ASystem *> _systems;
        std::vector<ASystem *> _systems;
    };
}

#endif //ECS_MEDIATOR_HPP

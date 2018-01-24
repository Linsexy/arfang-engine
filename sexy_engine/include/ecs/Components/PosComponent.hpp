//
// Created by benito on 1/4/18.
//

#ifndef ECS_POSCOMPONENT_HPP
#define ECS_POSCOMPONENT_HPP

#include "ecs/Components/IComponent.hpp"

namespace Sex {
    struct PosComponent : public IComponent {
        PosComponent(int xx, int yy) : x(xx), y(yy) {}

        unsigned int x;
        unsigned int y;
    };
}

#endif //ECS_POSCOMPONENT_HPP

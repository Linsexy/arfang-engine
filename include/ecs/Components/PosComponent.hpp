//
// Created by benito on 1/4/18.
//

#ifndef ECS_POSCOMPONENT_HPP
#define ECS_POSCOMPONENT_HPP

#include "ecs/Components/IComponent.hpp"

namespace Af {
    struct PosComponent : public IComponent {
        PosComponent(double xx, double yy) : x(xx), y(yy) {}

        double x;
        double y;
    };
}

#endif //ECS_POSCOMPONENT_HPP

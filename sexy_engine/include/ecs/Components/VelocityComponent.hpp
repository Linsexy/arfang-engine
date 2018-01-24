//
// Created by mymy on 24/01/18.
//

#ifndef RTYPE_VELOCITYCOMPONENT_HPP
#define RTYPE_VELOCITYCOMPONENT_HPP

#include "ecs/Components/IComponent.hpp"

namespace Sex
{
    struct VelocityComponent : IComponent
    {
        float velocity;

        VelocityComponent(float velocity) : velocity(velocity) {};
    };
}

#endif //RTYPE_VELOCITYCOMPONENT_HPP

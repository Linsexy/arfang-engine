//
// Created by mymy on 24/01/18.
//

#ifndef RTYPE_SPEEDATTACK_HPP
#define RTYPE_SPEEDATTACK_HPP

#include "ecs/Components/IComponent.hpp"

namespace Af
{
    struct SpeedAttack : IComponent
    {
        float speed;

        SpeedAttack(float speed) : speed(speed) {};
    };
}

#endif //RTYPE_SPEEDATTACK_HPP

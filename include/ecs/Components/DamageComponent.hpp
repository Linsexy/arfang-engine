//
// Created by mymy on 24/01/18.
//

#ifndef RTYPE_DAMAGECOMPONENT_HPP
#define RTYPE_DAMAGECOMPONENT_HPP

#include "ecs/Components/IComponent.hpp"

namespace Af
{
    struct DamageComponent : IComponent
    {
        int damage;
        DamageComponent(int damage) : damage(damage) {};
    };
}

#endif //RTYPE_DAMAGECOMPONENT_HPP

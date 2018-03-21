//
// Created by mymy on 24/01/18.
//

#ifndef RTYPE_LIFECOMPONENT_HPP
#define RTYPE_LIFECOMPONENT_HPP

#include "ecs/Components/IComponent.hpp"

namespace Sex
{
    struct LifeComponent : IComponent
    {
        unsigned int life;
        unsigned int lifeMax;

        LifeComponent(unsigned int life, unsigned int lifeMax) : life(life), lifeMax(lifeMax) {};
    };
}

#endif //RTYPE_LIFECOMPONENT_HPP

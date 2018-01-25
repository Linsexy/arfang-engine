//
// Created by benito on 1/4/18.
//

#ifndef ECS_TYPECOMPONENT_HPP
#define ECS_TYPECOMPONENT_HPP

#include "ecs/Components/IComponent.hpp"

namespace Sex
{
    struct TypeComponent : public IComponent
    {
        enum EntityType
        {
            HERO,
            HERO_SHOOT,
            ENNEMY,
            ENNEMY_SHOOT,
            DESTROYABLE,
            OBSTACLE,
            POWERUP
        };

        EntityType		type;

        TypeComponent(EntityType const &nType) : type(nType) {}
    };
}

#endif //ECS_TYPECOMPONENT_HPP

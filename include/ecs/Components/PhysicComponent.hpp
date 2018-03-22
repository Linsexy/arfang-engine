//
// Created by zgore on 24/01/18.
//

#ifndef RTYPE_PHYSICCOMPONENT_HPP
#define RTYPE_PHYSICCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../../../client/include/Tools.hpp"

namespace Af
{
    struct PhysicComponent : public IComponent
    {
        float           velocity;
        Af::Vector2D   dir;
        bool            isCollidable;

        PhysicComponent(float v, Af::Vector2D& d, bool c) : velocity(v), dir(d), isCollidable(c) {}
    };
}

#endif //RTYPE_PHYSICCOMPONENT_HPP

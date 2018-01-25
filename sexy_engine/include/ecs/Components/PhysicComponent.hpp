//
// Created by zgore on 24/01/18.
//

#ifndef RTYPE_PHYSICCOMPONENT_HPP
#define RTYPE_PHYSICCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../../../client/include/Tools.hpp"

namespace Sex
{
    struct PhysicComponent : public IComponent
    {
        float           velocity;
        Sex::Vector2D   dir;
        bool            isCollidable;

        PhysicComponent(float v, Sex::Vector2D& d, bool c) : velocity(v), dir(d), isCollidable(c) {}
    };
}

#endif //RTYPE_PHYSICCOMPONENT_HPP

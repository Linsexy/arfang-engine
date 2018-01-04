//
// Created by benito on 1/4/18.
//

#ifndef ECS_POSCOMPONENT_HPP
#define ECS_POSCOMPONENT_HPP

#include "IComponent.hpp"

struct PosComponent : public IComponent
{
    int x;
    int y;
};

#endif //ECS_POSCOMPONENT_HPP

//
// Created by mymy on 11/01/18.
//

#ifndef RTYPE_DIMENSION_HPP
#define RTYPE_DIMENSION_HPP

#include "ecs/Components/IComponent.hpp"

struct DimensionComponent : public IComponent
{
    DimensionComponent(unsigned int w, unsigned int h) : width(w), height(h) {};

    unsigned int width;
    unsigned int height;
};

#endif //RTYPE_DIMENSION_HPP

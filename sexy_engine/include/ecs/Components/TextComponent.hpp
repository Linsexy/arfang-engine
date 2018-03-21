//
// Created by renaud_q on 17/01/18.
//

#ifndef RTYPE_TEXTCOMPONENT_HPP
#define RTYPE_TEXTCOMPONENT_HPP

#include <string>
#include "Tools.hpp"
#include <ecs/Components/IComponent.hpp>

namespace Sex
{
    struct TextComponent : public IComponent
    {
        std::string     text;
        std::string     police;
        unsigned int    size;
        Vector2D        offset;
        Color           color;

        TextComponent() = delete;
        TextComponent(std::string const &text, std::string const &police, unsigned int size,
                      Vector2D const &newoffset, Color const &color):
                text(text),  police(police), size(size), offset(newoffset), color(color) {}
    };
}

#endif //RTYPE_TEXTCOMPONENT_HPP

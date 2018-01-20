//
// Created by renaud_q on 17/01/18.
//

#ifndef RTYPE_TEXTCOMPONENT_HPP
#define RTYPE_TEXTCOMPONENT_HPP

#include <string>
#include <ecs/Components/IComponent.hpp>

namespace Sex
{
    struct TextComponent : public IComponent
    {
        std::string     _text;
        std::string     _police;
        unsigned int    _size;

        TextComponent() = delete;
        TextComponent(std::string const &text, std::string const &police, unsigned int size): _text(text), _size(size),
        _police(police) {}
    };
}

#endif //RTYPE_TEXTCOMPONENT_HPP

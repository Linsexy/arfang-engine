//
// Created by renaud_q on 20/01/18.
//

#ifndef RTYPE_BUTTONCOMPONENT_HPP
#define RTYPE_BUTTONCOMPONENT_HPP

#include "IComponent.hpp"

namespace Sex {
    struct ButtonComponent : public IComponent {
        bool            isClicked;

        ButtonComponent(): isClicked(false) {}
    };
}

#endif //RTYPE_BUTTONCOMPONENT_HPP

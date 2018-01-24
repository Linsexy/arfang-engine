//
// Created by mymy on 24/01/18.
//

#ifndef RTYPE_WEAPONCOMPONENT_HPP
#define RTYPE_WEAPONCOMPONENT_HPP

#include "ecs/Components/IComponent.hpp"
#include "utils/IndexType.hpp"

namespace Sex
{
    struct WeaponComponent : IComponent
    {
        utils::IndexType::meta type;

        WeaponComponent(utils::IndexType::meta const &type) : type(type) {};
    };
}

#endif //RTYPE_WEAPONCOMPONENT_HPP

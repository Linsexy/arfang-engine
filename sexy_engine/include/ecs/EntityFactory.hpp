//
// Created by benito on 1/12/18.
//

#ifndef RTYPE_ENTITYFACTORY_HPP
#define RTYPE_ENTITYFACTORY_HPP

#include "Module.hpp"

namespace Sex {
    class EntityFactory : public Module<EntityFactory>
    {
        EntityFactory(Mediator *m) : Module<EntityFactory>(m)
        {}
        virtual ~EntityFactory() = default;

        //static
    };
}
#endif //RTYPE_ENTITYFACTORY_HPP

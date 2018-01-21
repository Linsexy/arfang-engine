//
// Created by benito on 1/21/18.
//

#ifndef RTYPE_ENTITYMANAGER_HPP
#define RTYPE_ENTITYMANAGER_HPP

#include <DLLoader/DLLoader.hpp>
#include "Module.hpp"

namespace Sex {
    class EntityManager : public Module<EntityManager,
                                        EntityFactory::Query> {
    public:
        EntityManager(const utils::DLLoader &);

        void handle(const EntityFactory::Query &);

    private:
        utils::DLLoader &dlLoader;
    };
}
#endif //RTYPE_ENTITYMANAGER_HPP

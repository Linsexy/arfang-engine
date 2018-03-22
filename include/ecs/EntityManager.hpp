//
// Created by benito on 1/21/18.
//

#ifndef RTYPE_ENTITYMANAGER_HPP
#define RTYPE_ENTITYMANAGER_HPP

#include <DLLoader/DLLoader.hpp>
#include "Module.hpp"
#include "Protocol/Events/SGEvent.hpp"

namespace Af {
    class EntityManager : public Module<EntityManager,
                                        EntityFactory::Query, Proto::CConnectGameEvent> {
    public:
        EntityManager(const std::shared_ptr<Mediator>&, utils::DLLoader &);

        void handle(const EntityFactory::Query &);
        void handle(const Proto::CConnectGameEvent &);

    private:
        utils::DLLoader &dlLoader;
        std::vector<std::string>    _paths;
    };
}
#endif //RTYPE_ENTITYMANAGER_HPP

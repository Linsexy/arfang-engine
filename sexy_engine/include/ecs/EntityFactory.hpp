//
// Created by benito on 1/12/18.
//

#ifndef RTYPE_ENTITYFACTORY_HPP
#define RTYPE_ENTITYFACTORY_HPP

#include <unordered_map>
#include <utils/IndexType.hpp>
#include <ecs/GameObject.hpp>

namespace Sex {
    class EntityFactory
    {
        class MetaObject
        {
            utils::IndexType::meta type;
            std::function<std::shared_ptr<GameObject>()> instantiate;
        };

    public:
        static std::shared_ptr<GameObject> create(utils::IndexType::meta);

    private:
        std::unordered_map<utils::IndexType::meta, MetaObject> typeToHandler;
    };
}

#endif //RTYPE_ENTITYFACTORY_HPP

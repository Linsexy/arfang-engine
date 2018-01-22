//
// Created by benito on 1/12/18.
//

#ifndef RTYPE_ENTITYFACTORY_HPP
#define RTYPE_ENTITYFACTORY_HPP

#include <unordered_map>
#include <utils/IndexType.hpp>
#include <ecs/GameObject.hpp>
#include <functional>

namespace Sex {
    class EntityFactory
    {
        using meta = unsigned int;
        using creator = std::function<std::shared_ptr<GameObject>()>;

        struct MetaObject
        {
            MetaObject(const creator& i) : instantiate(i) {}
            creator instantiate;
            /* could have more infos */
        };

    public:
        struct Query
        {
            std::vector<std::string> paths;
        };

        struct Response
        {
            Response(std::vector<utils::IndexType::meta>&&, const std::string&);
            std::vector<utils::IndexType::meta> types;
            std::string path;
        };

        static std::shared_ptr<GameObject> create(utils::IndexType::meta);
        static meta addMeta(const std::unique_ptr<GameObject::Loader>&) noexcept ;

    private:
       static std::unordered_map<utils::IndexType::meta, MetaObject> typeToHandler;
    public:
        static meta __inc;
    };
}

#endif //RTYPE_ENTITYFACTORY_HPP

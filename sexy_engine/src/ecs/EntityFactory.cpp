//
// Created by benito on 1/21/18.
//

#include <ecs/EntityFactory.hpp>

std::unordered_map<utils::IndexType::meta, Sex::EntityFactory::MetaObject> Sex::EntityFactory::typeToHandler;

std::shared_ptr<Sex::GameObject> Sex::EntityFactory::create(utils::IndexType::meta m)
{
    return (typeToHandler.at(m).instantiate());
}

void Sex::EntityFactory::addMeta(const std::unique_ptr<GameObject::Loader> &loader) noexcept
{
    typeToHandler.emplace(loader->type, MetaObject(loader->load));
}

Sex::EntityFactory::Response::Response(std::vector<utils::IndexType::meta> &&v, const std::string &s) : types(v), path(s)
{}
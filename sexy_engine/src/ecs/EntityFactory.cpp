//
// Created by benito on 1/21/18.
//

#include <ecs/EntityFactory.hpp>

std::unordered_map<utils::IndexType::meta, Sex::EntityFactory::MetaObject> Sex::EntityFactory::typeToHandler;
Sex::EntityFactory::meta Sex::EntityFactory::__inc = 1;

std::shared_ptr<Sex::GameObject> Sex::EntityFactory::create(Sex::EntityFactory::meta m)
{
    return (typeToHandler.at(m).instantiate());
}

Sex::EntityFactory::meta Sex::EntityFactory::addMeta(const std::unique_ptr<GameObject::Loader> &loader) noexcept
{
    typeToHandler.emplace(++__inc, MetaObject(loader->load));
    return (__inc);
}

Sex::EntityFactory::Response::Response(std::vector<utils::IndexType::meta> &&v, const std::string &s) : types(v), path(s)
{}
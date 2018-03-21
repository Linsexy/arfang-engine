//
// Created by benito on 1/21/18.
//

#include <ecs/EntityFactory.hpp>

std::unordered_map<utils::IndexType::meta, Sex::EntityFactory::MetaObject> Sex::EntityFactory::typeToHandler;

std::shared_ptr<Sex::GameObject> Sex::EntityFactory::create(utils::IndexType::meta m)
{
    return (typeToHandler.at(m).instantiate());
}

std::shared_ptr<Sex::GameObject> Sex::EntityFactory::create(utils::IndexType::meta m, unsigned int id)
{
    auto ret = typeToHandler.at(m).instantiate();
    ret->setId(id);
    return (ret);
}

void Sex::EntityFactory::addMeta(const std::unique_ptr<GameObject::Loader> &loader) noexcept
{
    auto nimoft = typeToHandler.emplace(loader->type, MetaObject(loader->load));
    std::cout << "emplace = " << std::boolalpha << nimoft.second << std::noboolalpha << std::endl;
}

Sex::EntityFactory::Response::Response(std::vector<utils::IndexType::meta> &&v, const std::string &s) : types(v), path(s)
{}
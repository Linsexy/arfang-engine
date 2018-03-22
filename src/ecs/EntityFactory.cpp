//
// Created by benito on 1/21/18.
//

#include <ecs/EntityFactory.hpp>

std::unordered_map<utils::IndexType::meta, Af::EntityFactory::MetaObject> Af::EntityFactory::typeToHandler;

std::shared_ptr<Af::GameObject> Af::EntityFactory::create(utils::IndexType::meta m)
{
    return (typeToHandler.at(m).instantiate());
}

std::shared_ptr<Af::GameObject> Af::EntityFactory::create(utils::IndexType::meta m, unsigned int id)
{
    auto ret = typeToHandler.at(m).instantiate();
    ret->setId(id);
    return (ret);
}

void Af::EntityFactory::addMeta(const std::unique_ptr<GameObject::Loader> &loader) noexcept
{
    auto nimoft = typeToHandler.emplace(loader->type, MetaObject(loader->load));
    std::cout << "emplace = " << std::boolalpha << nimoft.second << std::noboolalpha << std::endl;
}

Af::EntityFactory::Response::Response(std::vector<utils::IndexType::meta> &&v, const std::string &s) : types(v), path(s)
{}
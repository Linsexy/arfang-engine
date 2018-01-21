//
// Created by benito on 1/21/18.
//

#include <experimental/filesystem>
#include <ecs/EntityManager..hpp>

void Sex::EntityManager::handle(const EntityFactory::Query &query)
{
    std::vector<utils::IndexType::meta> types(query.paths.size());
    for (const auto& p : query.paths)
    {
        for (auto &p : std::experimental::filesystem::directory_iterator(p))
        {
            dlLoader.dlOpen(p.path().string());
            std::cout << "open with success" << std::endl;
            auto loader = (dlLoader.loadDLL<GameObject::Loader>(p.path().string(), "entryPoint"));
            types.push_back(loader->type);
            EntityFactory::addMeta(loader);
        }
    }
    transmit(EntityFactory::Response(std::move(types)));
}
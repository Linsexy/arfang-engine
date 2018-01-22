//
// Created by benito on 1/21/18.
//

#include <experimental/filesystem>
#include <ecs/EntityManager..hpp>

Sex::EntityManager::EntityManager(const std::shared_ptr<Mediator> &m, utils::DLLoader & d)
        : Module<EntityManager, EntityFactory::Query>(m), dlLoader(d)
{}

void Sex::EntityManager::handle(const EntityFactory::Query &query)
{
    std::vector<utils::IndexType::meta> types;
    types.reserve(query.paths.size());
    for (const auto& p : query.paths)
    {
        for (auto &p : std::experimental::filesystem::directory_iterator(p))
        {
            try {

                dlLoader.dlOpen(p.path().string());
                std::cout << "just opened with success " << p.path().string() << std::endl;
                auto loader = (dlLoader.loadDLL<GameObject::Loader>(p.path().string(), "entryPoint"));
                types.push_back(loader->type);
                EntityFactory::addMeta(loader);
                std::cout << "nimoftai " << loader->type << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    std::cout << "NIKAL " << types.size() << std::endl;
    transmit(EntityFactory::Response(std::move(types), query.paths.front()));
}
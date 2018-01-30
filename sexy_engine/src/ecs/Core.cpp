//
// Created by benito on 1/15/18.
//

#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <ecs/Core.hpp>
#include <DLLoader/DLErrors.hpp>
#include "../../../common/include/GameObject/Player.hpp"

void Sex::Core::go()
{
    try {
        //TODO : Abstraire la gestion du temps dans une classe qui retourne le temps écoulé et appelle la fonction.
        //TODO : Actuellement le temps ne permet pas de gérer sur des systèmes moins performants.
        //const auto frameTime = (1.0/60.0) * 1000.0;
        while (!isOver) {
            auto start = std::chrono::high_resolution_clock::now();

            for (auto &sys : _systems) {
                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = now - start;
                sys.second->update(elapsed.count());
            }
            //std::cout << (frameTime - elapsed) << std::endl;
            //auto sexy = (frameTime - elapsed) * 1000;
            //usleep(sexy > 0.0 ? sexy : 0);
            //std::cout << sexy << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

utils::DLLoader& Sex::Core::getDLLoader()
{
    return (dlLoader);
}

Sex::Core::Core()
        : Module<Core, Event>(std::make_shared<Mediator>(), "Core"), isOver(false)
{
    mediator->addSystem(this);
}

/*unsigned int Sex::Core::getIndexType() const noexcept
{
    return (utils::IndexType::get<Core>());
}*/

void Sex::Core::loadSystemsIn(const std::string &dirName)
{
	std::cout << "Opening the dir " <<  (std::string(ROOT_DIR) + "/" + dirName) << std::endl;
	for (auto &p : std::experimental::filesystem::directory_iterator(std::string(ROOT_DIR) + "/" + dirName)) {
		std::cout << "Try t<o open " << p << " with success" << std::endl;
		try {
            std::cout << p << std::endl;
			dlLoader.dlOpen(p.path().string());
			std::cout << "open with success" << std::endl;
			auto s = dlLoader.loadDLL<ASystem>(p.path().string(), "entryPoint",
                                                mediator);
            mediator->addSystem(s.get());
            auto i = s->getIndexType();
            _systems.emplace(i, std::move(s));
        }
        catch (const utils::DLErrors& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Sex::Core::loadEntitiesIn(const std::string &dirName)
{
    EntityFactory::Query   query;
    query.paths = { dirName };
    this->transmit(query);
}

void Sex::Core::setEntityDir(const std::string &s) {entitiesDir = s;}

void Sex::Core::setSystemDir(const std::string &s) {systemsDir = s;}

void Sex::Core::handle(const Event &e)
{
	if (e.t == Event::Type::END_LOOP)
		isOver = true;
}
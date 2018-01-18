//
// Created by benito on 1/15/18.
//

#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <ecs/Core.hpp>
#include <DLLoader/DLErrors.hpp>

void Sex::Core::go()
{
    try {

        while (!isOver) {
            for (auto &sys : _systems) {
                sys.second->update();
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

Sex::Core::Core()
        : Module<Core, Event>(std::make_shared<Mediator>(), "Core"), isOver(false)
{}

void Sex::Core::loadSystemsIn(const std::string &dirName)
{
    for (auto &p : std::experimental::filesystem::directory_iterator(dirName)) {
        try {
            dlLoader.dlOpen(p.path().string());
            dlLoader.dlSym(p.path().string(), "entryPoint");
        }
        catch (const utils::DLErrors& e)
        {
            std::cerr << e.what();
        }
        std::cout << p << std::endl;
    }
}

void Sex::Core::setEntityDir(const std::string &s) {entitiesDir = s;}

void Sex::Core::setSystemDir(const std::string &s) {systemsDir = s;}

void Sex::Core::handle(const Event &e)
{
    if (e.t == Event::Type::END_LOOP)
        isOver = true;
}
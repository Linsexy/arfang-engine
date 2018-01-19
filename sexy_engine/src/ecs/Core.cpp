//
// Created by benito on 1/15/18.
//

#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <ecs/Core.hpp>
#include <DLLoader/DLErrors.hpp>
#include <unistd.h>


void Sex::Core::go()
{
    try {
        //TODO : Abstraire la gestion du temps dans une classe qui retourne le temps écoulé et appelle la fonction.
        //TODO : Actuellement le temps ne permet pas de gérer sur des systèmes moins performants.
        const auto frameTime = (1.0/60.0) * 1000.0;
        while (!isOver) {
            auto start = std::chrono::high_resolution_clock::now();

            for (auto &sys : _systems) {
                auto now = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
                sys.second->update(elapsed);
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
//
// Created by benito on 1/15/18.
//

#include <ecs/Core.hpp>

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

void Sex::Core::setEntityDir(const std::string &s) {entitiesDir = s;}

void Sex::Core::setSystemDir(const std::string &s) {systemsDir = s;}

void Sex::Core::handle(const Event &e)
{
    if (e.t == Event::Type::END_LOOP)
        isOver = true;
}
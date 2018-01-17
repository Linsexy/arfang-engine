//
// Created by benito on 1/15/18.
//

#include <ecs/Core.hpp>

void Sex::Core::go()
{
    while (!isOver)
    {
        for (auto& sys : _systems)
        {
            sys.second->update();
        }
    }
}

Sex::Core::Core() : Module<Core, Event>(std::make_shared<Mediator>()), isOver(false)
{}

void Sex::Core::handle(const Event &e)
{
    if (e.t == Event::Type::END_LOOP)
        isOver = true;
}
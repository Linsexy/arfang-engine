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
            sys->update();
        }
    }
}
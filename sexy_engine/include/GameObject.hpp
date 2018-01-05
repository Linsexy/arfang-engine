//
// Created by benito on 1/4/18.
//

#ifndef ECS_GAMEOBJECT_HPP
#define ECS_GAMEOBJECT_HPP

//Stands for "entities" in a ECS design pattern

#include <unordered_map>
#include "IComponent.hpp"

class GameObject
{
public:
    GameObject() = default;
    ~GameObject() = default;

    template <typename CT, typename... Args>
    void attachComponent() noexcept
    {
        //static_assert()
    }


private:
    std::unordered_map<unsigned int, IComponent> _components;
};

#endif //ECS_GAMEOBJECT_HPP

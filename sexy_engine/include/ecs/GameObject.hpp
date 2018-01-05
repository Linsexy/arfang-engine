//
// Created by benito on 1/4/18.
//

#ifndef ECS_GAMEOBJECT_HPP
#define ECS_GAMEOBJECT_HPP

//Stands for "entities" in a ECS design pattern

#include <unordered_map>
#include <memory>
#include "IComponent.hpp"
#include "utils/IndexType.hpp"

class GameObject
{
public:
    GameObject() = default;
    ~GameObject() = default;

    template <typename CT, typename... Args>
    void attachComponent(Args const&... args) noexcept
    {
        static_assert(std::is_base_of<IComponent, CT>::value,
                      "You have to attach components, not ponies.");

        _components.emplace(utils::IndexType::get<CT>(), std::make_shared<CT>(args...));
    }

    template <typename CT>
    CT& getComponent()
    {
        static_assert(std::is_base_of<IComponent, CT>::value,
                      "You have to attach components, not ponies.");

        auto& ptr= _components.at(utils::IndexType::get<CT>());
        return (static_cast<CT&>(*ptr));
    }


private:
    std::unordered_map<unsigned int, std::shared_ptr<IComponent>> _components;
};

#endif //ECS_GAMEOBJECT_HPP

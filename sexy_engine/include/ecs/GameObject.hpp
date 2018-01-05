//
// Created by benito on 1/4/18.
//

#ifndef ECS_GAMEOBJECT_HPP
#define ECS_GAMEOBJECT_HPP

#include <unordered_map>
#include <memory>
#include "IComponent.hpp"
#include "utils/IndexType.hpp"

//Stands for "entities" in a ECS design pattern

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

    template <typename CT>
    bool hasComponent() noexcept
    {
        return (_components.find(utils::IndexType::get<CT>()) != _components.end());
    }

    template <typename CT>
    void detachComponent()
    {
        auto it _components.find(utils::IndexType::get<CT>()) != _components.end();
        if (it == _components.end())
        {
            throw (std::out_of_range("Component not in Entity"));
        }
        _components.erase(it);
    }

private:
    std::unordered_map<unsigned int, std::shared_ptr<IComponent>> _components;
};

#endif //ECS_GAMEOBJECT_HPP

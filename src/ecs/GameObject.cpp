//
// Created by benito on 1/12/18.
//

#include <ecs/GameObject.hpp>

Af::GameObject::EntityId Af::GameObject::id = 0;

Af::GameObject::GameObject()  : _id(++id)
{}

Af::GameObject::GameObject(EntityId id) : _id(id)
{
    ++id;
}

Af::GameObject::EntityId Af::GameObject::getId() const noexcept
{
    return _id;
}

void Af::GameObject::setId(EntityId id) noexcept
{
    _id = id;
}
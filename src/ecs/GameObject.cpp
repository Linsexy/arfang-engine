//
// Created by benito on 1/12/18.
//

#include <ecs/GameObject.hpp>

unsigned int Af::GameObject::id = 0;

Af::GameObject::GameObject()  : _id(++id)
{}

Af::GameObject::GameObject(unsigned int id) : _id(id)
{
    ++id;
}

unsigned int Af::GameObject::getId() const noexcept
{
    return _id;
}

void Af::GameObject::setId(unsigned int id) noexcept
{
    _id = id;
}
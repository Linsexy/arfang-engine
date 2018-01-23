//
// Created by benito on 1/12/18.
//

#include <ecs/GameObject.hpp>

unsigned int Sex::GameObject::__id__ = 0;

Sex::GameObject::GameObject()  : _id(++__id__)
{}

Sex::GameObject::GameObject(unsigned int id) : _id(id)
{
    ++__id__;
}

unsigned int Sex::GameObject::getId() const
{
    return _id;
}

void Sex::GameObject::setId(unsigned int id)
{
    _id = id;
}
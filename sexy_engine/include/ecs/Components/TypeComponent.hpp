//
// Created by benito on 1/4/18.
//

#ifndef ECS_TYPECOMPONENT_HPP
#define ECS_TYPECOMPONENT_HPP

#include "ecs/Components/IComponent.hpp"

enum EntityType
{
	HERO,
	HERO_SHOOT,
	ENNEMY,
	ENNEMY_SHOOT,
	DESTROYABLE,
	OBSTACLE,
	POWERUP
};

struct TypeComponent : public IComponent
{
	EntityType		type;

	TypeComponent(EntityType const &nType) : type(nType) {}
};

#endif //ECS_TYPECOMPONENT_HPP

#pragma once

#include <string>

#include "ecs/Components/IComponent.hpp"
#include <Tools.hpp>

namespace Sex
{
	struct SpriteComponent : public IComponent
	{
		struct SpriteData
		{
			std::string				image;
			Sex::Vector2D			size;
			int 					depth;
		};
		SpriteData				    	sprite;

		struct AnimationData
		{
			unsigned int			length;
			unsigned int			number;
			unsigned int			frame;
		};
		AnimationData				animation;
		Vector2D        			offset;

		enum Direction
		{
			EAST,
			WEST,
            DEFAULT
		};

		Direction 				direction;

		SpriteComponent() = delete;
		SpriteComponent(SpriteData const &newSprite, AnimationData const &newAnimation, Vector2D const &newoffset, Direction direction) :
				sprite(newSprite), animation(newAnimation), offset(newoffset), direction(direction){};
	};
}
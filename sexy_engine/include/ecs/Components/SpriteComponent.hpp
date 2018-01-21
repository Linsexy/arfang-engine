#pragma once

#include <string>

#include "ecs/Components/IComponent.hpp"
#include "ecs/Components/PosComponent.hpp"
#include "ecs/Components/DimensionComponent.hpp"
#include <Tools.hpp>

namespace Sex
{
	struct SpriteComponent : public IComponent
	{
		struct SpriteData
		{
			std::string				image;
			Sex::Vector2D			size;
			Sex::Vector2D			displaySize;
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


		SpriteComponent() = delete;
		SpriteComponent(SpriteData const &newSprite, AnimationData const &newAnimation, Vector2D const &newoffset) :
				sprite(newSprite), animation(newAnimation), offset(newoffset) {}
	};
}
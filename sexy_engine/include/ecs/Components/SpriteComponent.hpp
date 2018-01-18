#pragma once

#include <string>

#include "Graphical/Tools.hpp"
#include "ecs/Components/IComponent.hpp"
#include "ecs/Components/PosComponent.hpp"
#include "ecs/Components/DimensionComponent.hpp"

namespace Graphical
{
	struct SpriteComponent : public IComponent
	{
		struct SpriteData
		{
			std::string				image;
			Vector2D				size;
			Vector2D				displaySize;
			unsigned int		    depth;
		};
		SpriteData					sprite;

		struct AnimationData
		{
			unsigned int			length;
			unsigned int			number;
			unsigned int			frame;
		};
		AnimationData				animation;

		SpriteComponent() = delete;
		SpriteComponent(SpriteData const &newSprite, AnimationData const &newAnimation) : sprite(newSprite), animation(newAnimation) {}
	};
}
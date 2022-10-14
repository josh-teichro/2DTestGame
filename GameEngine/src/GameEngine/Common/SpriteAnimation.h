#pragma once

#include <glm/glm.hpp>

#include "GameEngine/Common/TextureAtlas.h"

namespace GameEngine
{

	class SpriteAnimation
	{
	public:
		SpriteAnimation();
		SpriteAnimation(const TextureAtlas& textureAtlas, glm::ivec2 startFrame, int numFrames);

	public:
		TextureAtlas textureAtlas;
		float framesPerSec = 20.0f;
		Color color = { 1.0f, 1.0f, 1.0f, 1.0f };

		glm::ivec2 startFrame = { 1, 1 };
		int numFrames = 1;
	};

}

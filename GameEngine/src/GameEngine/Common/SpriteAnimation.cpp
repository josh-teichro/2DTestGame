#include "gepch.h"

#include "GameEngine/Common/SpriteAnimation.h"

namespace GameEngine
{

	SpriteAnimation::SpriteAnimation()
	{
	}

	SpriteAnimation::SpriteAnimation(const TextureAtlas& textureAtlas, glm::ivec2 startFrame, int numFrames) :
		textureAtlas(textureAtlas),
		startFrame(startFrame),
		numFrames(numFrames)
	{
	}

}

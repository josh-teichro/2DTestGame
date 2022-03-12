#pragma once

#include "GameEngine/Components/Component.h"
#include "GameEngine/Renderer/Texture.h"
#include "GameEngine/Common/Common.h"

namespace GameEngine
{

	class Sprite : public Component
	{
	public:
		Ref<Texture2D> texture;

		Rect textureRect = FullRect;
		glm::vec2 textureOffset = { 0.0f, 0.0f };
		glm::vec2 textureScale = { 1.0f, 1.0f };

		const static Rect FullRect;

	};

}

#pragma once

#include "gepch.h"

#include "GameEngine/Renderer/Texture.h"

#include <glm/glm.hpp>

namespace GameEngine
{

	class RectTexture : public Component
	{
	public:
		virtual ~RectTexture() = default;

		Ref<Texture2D> baseTexture;
		glm::vec2 textureCoords[2] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 1.0f }
		};
	};

}
#pragma once

#include "gepch.h"

#include "GameEngine/Components/RectTexture.h"

#include <glm/glm.hpp>

namespace GameEngine
{

	class RectMaterial : public Component
	{
	public:
		virtual ~RectMaterial() = default;

		RectTexture texture;
		glm::vec2 textureOffset = { 0.0f, 0.0f };
		glm::vec2 textureScale = { 1.0f, 1.0f };

		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

}

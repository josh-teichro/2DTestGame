#pragma once

#include "gepch.h"

#include "GameEngine/Components/Component.h"

#include <glm/glm.hpp>

namespace GameEngine
{

	class RectTransform : public Component
	{
	public:
		virtual ~RectTransform() = default;

		glm::vec2 position = { 0.0f, 0.0f };
		glm::vec2 size = { 1.0f, 1.0f };
		float rotation = 0.0f;
		float zIndex = 0.0f;
	};

}

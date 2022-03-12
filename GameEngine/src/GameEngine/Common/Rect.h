#pragma once

#include <glm/glm.hpp>

namespace GameEngine
{

	struct Rect
	{
		union {
			struct {
				float x;
				float y;
				float width;
				float height;
			};
			glm::vec2 data[2];
		};
	};

}

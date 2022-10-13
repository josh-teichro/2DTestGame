#pragma once

#include "GameEngine/Components/Component.h"
#include "GameEngine/Common/Common.h"

#include <glm/glm.hpp>

namespace GameEngine
{

	class SpriteAnimator : public Component
	{
	public:
		SpriteAnimator();

		virtual void OnStart() override;
		virtual void OnUpdate() override;

		void SetTextureAtlas(TextureAtlas textureAtlas);

	public:
		float framesPerSec = 5.0f;
		Color color = { 1.0f, 1.0f, 1.0f, 1.0f };

		glm::ivec2 startFrame = { -1, -1 };
		int numFrames = -1;
		int curFrame = 0;

	private:
		TextureAtlas m_textureAtlas;

		glm::ivec2 m_curFramePos;
		float m_frameTime;

	private:
		void GetNextFrame();
		void IncY();

	};

}

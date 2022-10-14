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

		void AddAnimation(std::string name, SpriteAnimation animation);
		void RemoveAnimation(std::string name);

		Ref<SpriteAnimation> GetCurrentAnimation();
		void SetCurrentAnimation(std::string name);

	public:
		int curFrame;

	private:
		std::unordered_map<std::string, SpriteAnimation> m_animations;
		SpriteAnimation m_curAnimation;

		float m_curFrameTime;
		glm::ivec2 m_curFramePos;

	private:
		virtual void OnStart() override;
		virtual void OnUpdate() override;

		void GetNextFrame();

		void IncY();

	};

}

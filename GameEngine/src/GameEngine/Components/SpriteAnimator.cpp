#include "gepch.h"

#include "GameEngine/Components/SpriteAnimator.h"
#include "GameEngine/Core/Time.h"
#include "GameEngine/Renderer/Renderer2D.h"
#include "GameEngine/Core/GameObject.h"


namespace GameEngine
{
	SpriteAnimator::SpriteAnimator() :
		curFrame(0),
		m_curFrameTime(0.0f),
		m_curFramePos({ 0.0f, 0.0f })
	{
	}

	void SpriteAnimator::AddAnimation(std::string name, SpriteAnimation animation)
	{
		m_animations[name] = animation;
	}

	void SpriteAnimator::RemoveAnimation(std::string name)
	{
		m_animations.erase(name);
	}

	Ref<SpriteAnimation> SpriteAnimator::GetCurrentAnimation()
	{
		return MakeRef<SpriteAnimation>(m_curAnimation);
	}

	void SpriteAnimator::SetCurrentAnimation(std::string name)
	{
		m_curAnimation = m_animations[name];
		curFrame = 0;
		m_curFramePos = m_curAnimation.startFrame;
	}

	void SpriteAnimator::OnStart()
	{
	}

	void SpriteAnimator::OnUpdate()
	{
		float deltaTime = Time::GetDeltaTime();

		GameEngine::Renderer2D::DrawRect(*(GetGameObject()->transform), m_curAnimation.textureAtlas.GetBaseTexture(), m_curAnimation.textureAtlas.Get(m_curFramePos.x, m_curFramePos.y), m_curAnimation.color);

		m_curFrameTime += deltaTime;

		while (m_curFrameTime > 1 / m_curAnimation.framesPerSec)
		{
			GetNextFrame();
			m_curFrameTime -= 1 / m_curAnimation.framesPerSec;
		}
	}

	void SpriteAnimator::GetNextFrame()
	{
		curFrame++;

		if (curFrame >= m_curAnimation.numFrames)
		{
			curFrame = 0;
			m_curFramePos = m_curAnimation.startFrame;
		}
		else
		{
			m_curFramePos.x++;

			if (m_curFramePos.x >= (int)m_curAnimation.textureAtlas.GetCols())
			{
				m_curFramePos.x = 0;
				IncY();
			}
		}
	}

	void SpriteAnimator::IncY()
	{
		m_curFramePos.y++;

		if (m_curFramePos.y >= (int)m_curAnimation.textureAtlas.GetRows())
		{
			m_curFramePos.x = 0;
			m_curFramePos.y = 0;
		}
	}
}

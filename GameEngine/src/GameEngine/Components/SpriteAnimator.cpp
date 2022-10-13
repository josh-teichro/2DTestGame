#include "gepch.h"

#include "GameEngine/Components/SpriteAnimator.h"
#include "GameEngine/Core/GameObject.h"
#include "GameEngine/Core/Time.h"
#include "GameEngine/Renderer/Renderer2D.h"

namespace GameEngine
{

	SpriteAnimator::SpriteAnimator() :
		m_curFramePos({0.0f, 0.0f}),
		m_frameTime(0.0f)
	{
	}

	void SpriteAnimator::OnStart()
	{
	}

	void SpriteAnimator::OnUpdate()
	{
		float deltaTime = Time::GetDeltaTime();

		GameEngine::Renderer2D::DrawRect(*(GetGameObject()->transform), m_textureAtlas.GetBaseTexture(), m_textureAtlas.Get(m_curFramePos.x, m_curFramePos.y), color);

		m_frameTime += deltaTime;

		while (m_frameTime > 1 / framesPerSec)
		{
			GetNextFrame();
			m_frameTime -= 1 / framesPerSec;
		}
	}

	void SpriteAnimator::SetTextureAtlas(TextureAtlas textureAtlas) { 
		m_textureAtlas = textureAtlas; 

		if (startFrame.x < 0)
			startFrame.x = 0;

		if (startFrame.y < 0)
			startFrame.y = 0;

		if (numFrames < 0)
			numFrames = textureAtlas.GetCols() * textureAtlas.GetRows();
	}

	void SpriteAnimator::GetNextFrame()
	{
		curFrame++;

		if (curFrame >= numFrames)
		{
			curFrame = 0;
			m_curFramePos = startFrame;
		}
		else 
		{
			m_curFramePos.x++;

			if (m_curFramePos.x >= (int)m_textureAtlas.GetCols())
			{
				m_curFramePos.x = 0;
				IncY();
			}
		}
	}

	void SpriteAnimator::IncY()
	{
		m_curFramePos.y++;

		if (m_curFramePos.y >= (int)m_textureAtlas.GetRows())
		{
			m_curFramePos.x = 0;
			m_curFramePos.y = 0;
		}
	}

}

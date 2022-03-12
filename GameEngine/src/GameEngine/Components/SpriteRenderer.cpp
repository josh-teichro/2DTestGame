#include "gepch.h"
#include "SpriteRenderer.h"

#include "GameEngine/Core/GameObject.h"
#include "GameEngine/Renderer/Renderer2D.h"

namespace GameEngine
{

	SpriteRenderer::SpriteRenderer()
	{
	}

	void SpriteRenderer::OnStart()
	{
		m_sprite = GetGameObject()->GetComponent<Sprite>();

		if (!m_sprite)
		{
			GE_ERROR("SpriteRenderer requires a Sprite!");
		}
	}

	void SpriteRenderer::OnUpdate()
	{
		GameEngine::Renderer2D::DrawRect(*(GetGameObject()->transform), *m_sprite, color);
	}

}

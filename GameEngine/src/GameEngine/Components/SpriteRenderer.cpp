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
		Rect rect = {
			m_sprite->textureOffset.x + m_sprite->textureRect.x,
			m_sprite->textureOffset.y + m_sprite->textureRect.y,
			m_sprite->textureScale.y * m_sprite->textureRect.width,
			m_sprite->textureScale.y * m_sprite->textureRect.height,
		};

		Renderer2D::DrawRect(*(GetGameObject()->transform), m_sprite->texture, rect, color);
	}

}

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
		m_rectMaterial = GetGameObject()->GetComponent<RectMaterial>();

		if (!m_rectMaterial)
		{
			GE_ERROR("SpriteRenderer requires a RectMaterial!");
		}
	}

	void SpriteRenderer::OnUpdate()
	{
		GameEngine::Renderer2D::DrawRect(*(GetGameObject()->transform), *m_rectMaterial);
	}

}

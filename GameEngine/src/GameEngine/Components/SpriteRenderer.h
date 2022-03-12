#pragma once

#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/Sprite.h"
#include "GameEngine/Renderer/Texture.h"
#include "GameEngine/Common/Common.h"

namespace GameEngine
{

	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();

		virtual void OnStart() override;
		virtual void OnUpdate() override;

	public:
		Color color = {1.0f, 1.0f, 1.0f, 1.0f};

	private:
		Ref<Sprite> m_sprite;

	};

}

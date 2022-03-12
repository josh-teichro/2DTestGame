#pragma once

#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/RectMaterial.h"
#include "GameEngine/Renderer/Texture.h"

namespace GameEngine
{

	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();

		virtual void OnStart() override;
		virtual void OnUpdate() override;

	private:
		Ref<RectMaterial> m_rectMaterial;

	};

}

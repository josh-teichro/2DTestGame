#pragma once

#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/VertexArray.h"
#include "GameEngine/Renderer/RenderCommand.h"
#include "GameEngine/Renderer/Camera.h"
#include "GameEngine/Renderer/Texture.h"

#include "GameEngine/Components/RectTransform.h"
#include "GameEngine/Components/Sprite.h"

#include <glm/glm.hpp>

namespace GameEngine {

	class Renderer2D {
	public:
		using API = RenderCommand::API;

		struct Statistics
		{
			uint32_t drawCalls = 0;
			uint32_t quadCount = 0;
			uint32_t vertexCount = 0;
			uint32_t indexCount = 0;
			uint32_t maxTextureSlotsUsed = 0;
		};

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Ref<Camera>& camera);
		static void EndScene();

		static void Flush();

		static void DrawRect(const RectTransform& transform, const Sprite& sprite, glm::vec4 color);

		static API GetAPI() { return RenderCommand::GetAPI(); }

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void Reset();

	};

}

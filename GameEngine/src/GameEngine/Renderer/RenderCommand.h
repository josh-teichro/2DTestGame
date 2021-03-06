#pragma once

#include "GameEngine/Renderer/RendererAPI.h"
#include "GameEngine/Core/Types.h"

namespace GameEngine
{

	class RenderCommand
	{
	public:
		using API = RendererAPI::API;

	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawArray(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			s_RendererAPI->DrawArray(vertexArray, indexCount);
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static API GetAPI() { return RendererAPI::GetAPI(); }
	
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}

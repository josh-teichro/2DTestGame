#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/EventManager.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

namespace GameEngine {

	/**
	* The main Application.
	*/
	class Application// : public HandlesEvents
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void EventCallback(const Event& e);

		bool OnWindowClose(const WindowCloseEvent& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_window; }

		inline static Application& Get() { return *s_instance; }

	private:
		static Application* s_instance;

		std::unique_ptr<Window> m_window;
		bool m_isRunning = true;

		LayerStack m_layerStack;

		ImGuiLayer* m_imGuiLayer;

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<VertexArray> m_vertexArray;

		std::shared_ptr<Shader> m_shader2;
		std::shared_ptr<VertexArray> m_vertexArray2;

	};

	/**
	* To be defined in Client.
	*
	* Must return an Application object.
	*/
	Application* CreateApplication();

}


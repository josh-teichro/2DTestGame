#pragma once

#include "Core.h"
#include "Window.h"
#include "Core/Time.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/EventManager.h"
#include "ImGui/ImGuiLayer.h"

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

		Scope<Window> m_window;
		Scope<Time> m_time;
		bool m_isRunning = true;

		LayerStack m_layerStack;

		ImGuiLayer* m_imGuiLayer;

	};

	/**
	* To be defined in Client.
	*
	* Must return an Application object.
	*/
	Application* CreateApplication();

}


#pragma once

#include "gepch.h"

#include "GameEngine/Core/Core.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/MouseEvent.h"

namespace GameEngine {

	/**
	* Props needed to create a Window.
	*/
	struct WindowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "Game Engine", 
					unsigned int width = 1280, 
					unsigned int height = 720) :
			title(title), width(width), height(height) {}
	};

	/**
	* Window abstraction. To be defined per platform.
	*/
	class Window {
	public:
		using EventCallbackFn = std::function<void(const Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}

#pragma once

#include "GameEngine/Core/Core.h"
#include "GameEngine/Core/GameObject.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/HandlesEvents.h"

namespace GameEngine {

	/**
	* A Layer defines a set of objects, etc. that will be rendered and will
	* receive events. Layers are rendered in a specific order which determines
	* which Layer will be rendered or receive events first. 
	*/
	class Layer : public HandlesEvents
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		/**
		* Called when the Layer is added to the Application.
		*/
		virtual void OnAttach();

		/**
		* Called when the Layer is removed from the Application.
		*/
		virtual void OnDetach();

		/**
		* Called every frame. Draw any objects, etc. here.
		*/
		virtual void OnUpdate();

		/**
		* Called every ImGui frame. Render any ImGui components here.
		*/
		virtual void OnImGuiUpdate();

		/**
		* Event callback.
		*/
		virtual bool OnEvent(const Event& e) override;

		/**
		* Get the Layer name (for debugging).
		*/
		inline const std::string& GetName() const { return m_debugName; }

		/**
		* Create a GameObject specific to this layer.
		*/
		Ref<GameObject> CreateGameObject();

		/**
		* Create a GameObject specific to this layer.
		*/
		Ref<GameObject> CreateGameObject(std::initializer_list<Ref<Component>> components);

		/**
		* Destroy a gameobject.
		*/
		void DestroyGameObject(Ref<GameObject> gameObject);

	private:
		std::string m_debugName;

		std::forward_list<Ref<GameObject>> m_objectPool;
	};

}

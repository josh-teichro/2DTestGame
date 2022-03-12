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
		* Get the Layer name (for debugging).
		*/
		inline const std::string& GetName() const { return m_debugName; }

		/**
		* Create a GameObject specific to this layer.
		*/
		template<typename...Args>
		Ref<GameObject> CreateGameObject(Args&&...args);

		Ref<GameObject> CreateGameObject(std::initializer_list<Ref<Component>> components);

	private:
		std::string m_debugName;

		std::vector<Ref<GameObject>> m_objectPool;
	};

	// -------------------------------------

	template<typename...Args>
	Ref<GameObject> Layer::CreateGameObject(Args&&...args)
	{
		Ref<GameObject> gameObject = MakeRef<GameObject>(std::forward<Args>(args)...);
		m_objectPool.push_back(gameObject);
		return gameObject;
	}

}

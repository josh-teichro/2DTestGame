#pragma once

#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/RectTransform.h"

namespace GameEngine
{

	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		static Ref<GameObject> CreateGameObject() { return CreateGameObject({}); }
		static Ref<GameObject> CreateGameObject(std::initializer_list<Ref<Component>> components) { return Ref<GameObject>(new GameObject(components)); }

		GameObject& operator=(std::initializer_list<Ref<Component>> components) { this->m_components = components; return *this; }

		template <typename T>
		Ref<T> AddComponent();

		template <typename T>
		Ref<T> GetComponent();

		std::vector<Ref<Component>> GetComponents() { return m_components; }

		Ref<RectTransform> GetTransform() { return transform; }

	private:
		GameObject() : GameObject({}) {}
		GameObject(const GameObject&) = delete;

		GameObject(std::initializer_list<Ref<Component>> components) :
			m_components(components),
			transform(MakeRef<RectTransform>()) {}

	public:
		Ref<RectTransform> transform;

	private:
		std::vector<Ref<Component>> m_components;

	};

	//
	// --------------------------------------
	//

	template<typename T>
	inline Ref<T> GameObject::AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Cannot add non-Component to GameObject using AddComponent");

		Ref<T> newComponentAsType = MakeRef<T>();
		Ref<Component> newComponent = std::static_pointer_cast<Component>(newComponentAsType);
		newComponent->m_gameObject = shared_from_this();
		m_components.push_back(newComponent);
		return newComponentAsType;
	}

	template<typename T>
	inline Ref<T> GameObject::GetComponent()
	{
		for (Ref<Component> component : m_components) 
		{
			Ref<T> temp = std::dynamic_pointer_cast<T>(component);

			if (temp)
			{
				return temp;
			}
		}

		return nullptr;
	}

}

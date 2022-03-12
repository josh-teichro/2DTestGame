#pragma once

#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/RectTransform.h"

namespace GameEngine
{

	class GameObject
	{
	public:
		GameObject() : GameObject({}) {}

		//GameObject(const GameObject&) = delete;
		GameObject(std::initializer_list<Ref<Component>> components) : 
			components(components), 
			transform(MakeRef<RectTransform>()) {}

		GameObject& operator=(std::initializer_list<Ref<Component>> components) { this->components = components; return *this; }

		template <typename T>
		Ref<T> AddComponent();

		template <typename T>
		Ref<T> GetComponent();

		std::vector<Ref<Component>> GetComponents() { return components; }

		Ref<RectTransform> GetTransform() { return transform; }

	private:
		std::vector<Ref<Component>> components;

		Ref<RectTransform> transform;

	};

	//
	// --------------------------------------
	//

	template<typename T>
	inline Ref<T> GameObject::AddComponent()
	{
		Ref<T> newComponent = MakeRef<T>();
		components.push_back(newComponent);
		return newComponent;
	}

	template<typename T>
	inline Ref<T> GameObject::GetComponent()
	{
		for (Ref<Component> component : components) 
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

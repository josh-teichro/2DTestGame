#include "gepch.h"

#include "GameEngine/Core/Layer.h"

namespace GameEngine {

	/**
	* Create a new Layer.
	*
	* name: name used for debugging
	*/
	Layer::Layer(const std::string& name) :
		m_debugName(name)
	{
	}

	void Layer::OnAttach()
	{

		for (Ref<GameObject> gameObject : m_objectPool)
		{
			for (Ref<Component> component : gameObject->GetComponents())
			{
				component->OnStart();
			}
		}
	}

	void Layer::OnDetach()
	{

		for (Ref<GameObject> gameObject : m_objectPool)
		{
			for (Ref<Component> component : gameObject->GetComponents())
			{
				component->OnDestroy();
			}
		}
	}

	void Layer::OnUpdate()
	{
		for (Ref<GameObject> gameObject : m_objectPool)
		{
			for (Ref<Component> component : gameObject->GetComponents())
			{
				component->OnUpdate();
			}
		}
	}

	void Layer::OnImGuiUpdate()
	{
		for (Ref<GameObject> gameObject : m_objectPool)
		{
			for (Ref<Component> component : gameObject->GetComponents())
			{
				component->OnImGuiUpdate();
			}
		}
	}

	Ref<GameObject> Layer::CreateGameObject(std::initializer_list<Ref<Component>> components)
	{
		Ref<GameObject> gameObject = MakeRef<GameObject>(components);
		m_objectPool.push_back(gameObject);
		return gameObject;
	}

}
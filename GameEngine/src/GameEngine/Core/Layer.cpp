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

	bool Layer::OnEvent(const Event& e)
	{
		if (HandlesEvents::OnEvent(e))
		{
			return true;
		}

		for (Ref<GameObject> gameObject : m_objectPool)
		{
			for (Ref<Component> component : gameObject->GetComponents())
			{
				if (component->OnEvent(e)) 
				{
					return true;
				}
			}
		}
	}

	Ref<GameObject> Layer::CreateGameObject()
	{
		return CreateGameObject({});
	}

	Ref<GameObject> Layer::CreateGameObject(std::initializer_list<Ref<Component>> components)
	{
		Ref<GameObject> gameObject = GameObject::CreateGameObject(components);
		m_objectPool.push_front(gameObject);
		return gameObject;
	}

	void Layer::DestroyGameObject(Ref<GameObject> gameObject)
	{
		m_objectPool.remove(gameObject);
	}

}
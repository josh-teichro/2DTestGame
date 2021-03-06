#pragma once

#include "gepch.h"

#include "GameEngine/Events/HandlesEvents.h"

namespace GameEngine 
{
	class GameObject;

	class Component : public HandlesEvents
	{
	public:
		virtual ~Component() = default;

		virtual void OnStart() {};

		virtual void OnDestroy() {};

		virtual void OnUpdate() {};

		virtual void OnImGuiUpdate() {};

		Ref<GameObject> GetGameObject() const;

	private:
		friend GameObject;

		WeakRef<GameObject> m_gameObject;

	};

}

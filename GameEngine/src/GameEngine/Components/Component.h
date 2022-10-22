#pragma once

#include "gepch.h"

#include "GameEngine/Events/HandlesEvents.h"

namespace GameEngine 
{
	class GameObject;
	class RectTransform;

	class Component : public HandlesEvents
	{
	public:
		bool enabled = true;

	public:
		virtual ~Component() = default;

		virtual void OnStart() {};

		virtual void OnDestroy() {};

		virtual void OnUpdate() {};

		virtual void OnImGuiUpdate() {};

		Ref<GameObject> GetGameObject() const;

		Ref<RectTransform> GetTransform() const;

	private:
		friend GameObject;

		WeakRef<GameObject> m_gameObject;

	};

}

#pragma once

#include "gepch.h"

#include "GameEngine/Events/HandlesEvents.h"

namespace GameEngine 
{

	class Component : public HandlesEvents
	{
	public:
		virtual ~Component() = default;

		virtual void OnStart() {};

		virtual void OnDestroy() {};

		virtual void OnUpdate() {};

		virtual void OnImGuiUpdate() {};

	};

}

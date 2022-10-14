#include "gepch.h"
#include "Component.h"

#include "GameEngine/Core/GameObject.h"

namespace GameEngine
{

    Ref<GameObject> Component::GetGameObject() const
    {
        if (!m_gameObject.expired())
        {
            return m_gameObject.lock();
        }
        else
        {
            GE_ERROR("Referencing a GameObject that has been destroyed!");
        }
    }

    Ref<RectTransform> Component::GetTransform() const
    {
        return GetGameObject()->GetTransform();
    }

}

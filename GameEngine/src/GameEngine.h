#pragma once

// For use by GameEngine applications

#include "GameEngine/Core/Core.h"
#include "GameEngine/Core/Application.h"
#include "GameEngine/Core/GameObject.h"
#include "GameEngine/Core/Layer.h"
#include "GameEngine/Core/Log.h"
#include "GameEngine/Core/Time.h"
#include "GameEngine/Core/Types.h"

// --- Components ---------------------------------
#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/CameraController2D.h"
#include "GameEngine/Components/CameraController3D.h"
#include "GameEngine/Components/RectTransform.h"
#include "GameEngine/Components/Sprite.h"
#include "GameEngine/Components/SpriteRenderer.h"
#include "GameEngine/Components/SpriteAnimator.h"
#include "GameEngine/Components/Transform.h"

// --- Events -------------------------------------
#include "GameEngine/Core/Input.h"
#include "GameEngine/Events/KeyCodes.h"
#include "GameEngine/Events/MouseCodes.h"
// ------------------------------------------------

// --- Renderer -----------------------------------
#include "GameEngine/Renderer/Renderer.h"
#include "GameEngine/Renderer/Renderer2D.h"
#include "GameEngine/Renderer/RenderCommand.h"
#include "GameEngine/Renderer/Camera.h"

#include "GameEngine/Renderer/VertexBuffer.h"
#include "GameEngine/Renderer/IndexBuffer.h"
#include "GameEngine/Renderer/VertexArray.h"
#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Texture.h"

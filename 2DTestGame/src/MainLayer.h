#pragma once

#include <GameEngine.h>
#include <string>
#include "Components/Player.h"

using namespace GameEngine;

class MainLayer : public GameEngine::Layer
{
public:
	MainLayer();
	virtual ~MainLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate() override;
	virtual void OnImGuiUpdate() override;

private:

	GameEngine::ShaderLibrary m_shaderLibrary;

	Ref<GameObject> m_playerObject;
	Ref<GameObject> m_background;
	Ref<GameObject> m_editorCamera;
	
	Ref<Player> m_player;

	bool m_followPlayer;

	// editor camera components references
	Ref<CameraController2D> m_cameraController;

private:
	void CreateScene();
	void ResetScene();
};

#pragma once

#include <GameEngine.h>

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

	virtual bool OnEvent(const GameEngine::Event& e) override;
	virtual bool OnKeyUp(const GameEngine::KeyUpEvent& e) override;

private:
	GameEngine::CameraController2D m_cameraController;

	GameEngine::ShaderLibrary m_shaderLibrary;

	// GameObjects
	Ref<GameObject> m_player;

	// red hood character
	const glm::vec2 c_characterSheetSize = { 1344, 1463 };
	const glm::vec2 c_characterSheetNumCells = { 12.0f, 11.0f };
	const glm::vec2 c_characterSheetCellSize = c_characterSheetSize / c_characterSheetNumCells;
	
	Ref<RectMaterial> m_characterMaterial;
	int32_t m_characterAnimationIndex;
	int32_t m_characterAnimationFrameIndex;
	float m_characterAnimationSpeed;
	float m_characterAnimationTime;

private:
	void CreateScene();
	void ResetScene();
};

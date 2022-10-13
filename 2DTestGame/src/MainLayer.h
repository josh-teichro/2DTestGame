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

private:

	GameEngine::ShaderLibrary m_shaderLibrary;

	// GameObjects
	Ref<GameObject> m_player;
	Ref<GameObject> m_cube;
	Ref<GameObject> m_editorCamera;

	// player components references
	const glm::vec2 c_characterSheetSize = { 1344, 1463 };
	const glm::vec2 c_characterSheetNumCells = { 12.0f, 11.0f };
	const glm::vec2 c_characterSheetCellSize = c_characterSheetSize / c_characterSheetNumCells;
	
	Ref<Sprite> m_characterSprite;
	Ref<SpriteAnimator> m_characterSpriteAnimator;
	int32_t m_characterAnimationIndex;

	// editor camera components references
	Ref<CameraController2D> m_cameraController;

private:
	void CreateScene();
	void ResetScene();
};

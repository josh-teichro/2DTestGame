#pragma once

#include <GameEngine.h>

using namespace GameEngine;

class Player : public Component
{
public:
	// supplementary types
	enum State
	{
		Idle,
		Running,
		Attacking
	};

	// variables
	float speed = 1.0f;

public:
	void Reset();
	void SetState(State newState);

	void Move(glm::vec2 direction);
	void Attack();

private:
	// constants
	const glm::vec2 c_characterSheetSize = { 1344, 1463 };
	const glm::vec2 c_characterSheetNumCells = { 12.0f, 11.0f };
	const glm::vec2 c_characterSheetCellSize = c_characterSheetSize / c_characterSheetNumCells;

	const std::string c_animations[11] = {
		"Die",
		"Heavy Slash",
		"Normal Slash",
		"Quick Slash",
		"One-Handed Slash",
		"Double Slash",
		"Slide",
		"Idle",
		"Bow Attack",
		"Dash 1",
		"Dash 2",
	};

	State m_state;

	// component references
	Ref<SpriteAnimator> m_characterSpriteAnimator;
	int32_t m_characterAnimationIndex;

	Ref<CameraController2D> m_cameraController;

private:
	virtual void OnStart() override;
	virtual void OnUpdate() override;

	virtual void OnImGuiUpdate() override;

	virtual bool OnMouseDown(const MouseDownEvent& e) override;

	glm::vec2 ReadInput();

};

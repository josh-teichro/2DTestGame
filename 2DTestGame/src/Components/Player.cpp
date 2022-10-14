#include "Player.h"

#include <imgui.h>

void Player::Reset()
{
	m_state = State::Idle;

	m_characterAnimationIndex = 0;

	m_characterSpriteAnimator->curFrame = 0;
	m_characterSpriteAnimator->SetCurrentAnimation("Idle");
}

void Player::SetState(State newState)
{
	if (m_state == newState)
		return;

	switch (newState)
	{
	default:
	case State::Idle:
		m_characterSpriteAnimator->SetCurrentAnimation("Idle");
		break;
	case State::Running:
		m_characterSpriteAnimator->SetCurrentAnimation("Dash 1");
		break;
	case State::Attacking:
		m_characterSpriteAnimator->SetCurrentAnimation("Heavy Slash");
		break;
	}

	m_state = newState;
}

void Player::OnStart()
{
	m_characterSpriteAnimator = GetGameObject()->AddComponent<SpriteAnimator>();

	Ref<Texture2D> texture = GameEngine::Texture2D::Create("./res/textures/red-hood-character-sheet.png");
	texture->SetFilter(GameEngine::Texture::Filter::Nearest);
	TextureAtlas textureAtlas = TextureAtlas(c_characterSheetNumCells[0], c_characterSheetNumCells[1], texture);

	for (int i = 0; i < c_characterSheetNumCells[1]; i++)
	{
		SpriteAnimation animation = SpriteAnimation(textureAtlas, { 0, i }, c_characterSheetNumCells[0]);
		m_characterSpriteAnimator->AddAnimation(c_animations[i], animation);
	}

	Reset();
}

void Player::OnUpdate()
{
	float deltaTime = Time::GetDeltaTime();
	bool isMoving = false;

	if (Input::GetKeyDown(KeyCode::W)) {
		GetTransform()->position.y += deltaTime * speed;
		isMoving = true;
	}
	else if (Input::GetKeyDown(KeyCode::S)) {
		GetTransform()->position.y -= deltaTime * speed;
		isMoving = true;
	}

	if (Input::GetKeyDown(KeyCode::A)) {
		GetTransform()->position.x -= deltaTime * speed;
		isMoving = true;
	}
	else if (Input::GetKeyDown(KeyCode::D)) {
		GetTransform()->position.x += deltaTime * speed;
		isMoving = true;
	}

	if (isMoving)
		SetState(State::Running);
	else
		SetState(State::Idle);
}

void Player::OnImGuiUpdate()
{
	ImGui::Text("Character");
	if (ImGui::BeginCombo("Animation", c_animations[m_characterAnimationIndex].c_str()))
	{
		for (int i = 0; i < (int)c_characterSheetNumCells[1]; i++)
		{
			bool is_selected = (m_characterAnimationIndex == i);
			if (ImGui::Selectable(c_animations[i].c_str(), is_selected)) {
				m_characterAnimationIndex = i;
				m_characterSpriteAnimator->SetCurrentAnimation(c_animations[i]);
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

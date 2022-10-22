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

void Player::Move(glm::vec2 moveDir)
{
	if (moveDir.x == 0.0f && moveDir.y == 0.0f)
		return;

	if (m_characterSpriteAnimator->GetCurrentAnimation() == "Quick Slash")
		return;

	float deltaTime = Time::GetDeltaTime();

	moveDir = glm::normalize(moveDir);
	GetTransform()->position += deltaTime * speed * moveDir;

	if (moveDir.x < 0.0f)
		GetTransform()->size.x = abs(GetTransform()->size.x);
	else if (moveDir.x > 0.0f)
		GetTransform()->size.x = -abs(GetTransform()->size.x);

}

void Player::Attack()
{
	m_characterSpriteAnimator->PlayOnce("Quick Slash");
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

	glm::vec2 moveDir = ReadInput();
	bool isMoving = (moveDir.x != 0.0f || moveDir.y != 0.0f);

	if (isMoving)
	{
		Move(moveDir);
		SetState(State::Running);
	}
	else
	{
		SetState(State::Idle);
	}
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

bool Player::OnMouseDown(const MouseDownEvent& e)
{
	Attack();

	return false;
}

glm::vec2 Player::ReadInput()
{
	glm::vec2 input = { 0.0f, 0.0f };

	if (Input::GetKeyDown(KeyCode::W) || Input::GetKeyDown(KeyCode::UpArrow)) {
		input.y += 1.0f;
	}
	else if (Input::GetKeyDown(KeyCode::S) || Input::GetKeyDown(KeyCode::DownArrow)) {
		input.y -= 1.0f;
	}

	if (Input::GetKeyDown(KeyCode::A) || Input::GetKeyDown(KeyCode::LeftArrow)) {
		input.x -= 1.0f;
	}
	else if (Input::GetKeyDown(KeyCode::D) || Input::GetKeyDown(KeyCode::RightArrow)) {
		input.x += 1.0f;
	}

	return input;
}

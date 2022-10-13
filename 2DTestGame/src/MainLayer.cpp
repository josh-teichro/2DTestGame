#include "MainLayer.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

MainLayer::MainLayer()
{
	CreateScene();
}

void MainLayer::OnAttach()
{
	Layer::OnAttach();

	ResetScene();
}

void MainLayer::OnDetach()
{
	Layer::OnDetach();
}

void MainLayer::OnUpdate()
{
	GE_PROFILE_FUNCTION();

	//Layer::OnUpdate();

	float deltaTime = GameEngine::Time::GetDeltaTime();

	// red hood character
	//m_characterAnimationTime += deltaTime;
	//while (m_characterAnimationTime > 1 / m_characterAnimationSpeed)
	//{
	//	m_characterAnimationFrameIndex = (m_characterAnimationFrameIndex + 1) % (int)c_characterSheetNumCells[1];
	//	m_characterAnimationTime -= 1 / m_characterAnimationSpeed;
	//}

	//m_characterSprite->textureRect.x = m_characterAnimationFrameIndex / c_characterSheetNumCells.x;
	//m_characterSprite->textureRect.y = m_characterAnimationIndex / c_characterSheetNumCells.y;
	//m_characterSprite->textureRect.width = 1.0f / c_characterSheetNumCells.x;
	//m_characterSprite->textureRect.height = 1.0f / c_characterSheetNumCells.y;

	//characterTexture.textureCoords[0] = glm::vec2(m_characterAnimationFrameIndex, m_characterAnimationIndex) / c_characterSheetNumCells;
	//characterTexture.textureCoords[1] = glm::vec2(m_characterAnimationFrameIndex + 1, m_characterAnimationIndex + 1) / c_characterSheetNumCells;

	// draw scene
	GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	GameEngine::RenderCommand::Clear();

	GameEngine::Renderer2D::ResetStats();
	GameEngine::Renderer2D::BeginScene(m_cameraController->GetCamera());

	Layer::OnUpdate();
	// draw character
	//GameEngine::Renderer2D::DrawRect(*m_player->GetTransform(), *m_characterSprite, {1.0f, 1.0f, 1.0f, 1.0f});

	GameEngine::Renderer2D::EndScene();
}

void MainLayer::OnImGuiUpdate()
{
	GE_PROFILE_FUNCTION();

	Layer::OnImGuiUpdate();

	ImGui::Text("Character");
	ImGui::DragFloat2("Position", glm::value_ptr(m_player->GetTransform()->position), 0.1f);
	if (ImGui::BeginCombo("Animation", std::to_string(m_characterAnimationIndex).c_str()))
	{
		for (int i = 0; i < (int)c_characterSheetNumCells[1]; i++)
		{
			bool is_selected = (m_characterAnimationIndex == i);
			if (ImGui::Selectable(std::to_string(i).c_str(), is_selected)) {
				m_characterAnimationIndex = i;
				m_characterSpriteAnimator->startFrame = { 0, i };
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();  
		}
		ImGui::EndCombo();
	}
	ImGui::DragFloat("Animation Speed", &m_characterSpriteAnimator->framesPerSec, 1.0f, 0.0f, 60.0f);

	Ref<Sprite> cubeSprite = m_cube->GetComponent<Sprite>();

	ImGui::Text("Sprite");
	ImGui::DragFloat2("Position##Sprite", glm::value_ptr(m_cube->GetTransform()->position), 0.1f);
	ImGui::DragFloat2("Texture Offset##Sprite", glm::value_ptr(cubeSprite->textureOffset), 0.1f);
	ImGui::DragFloat2("Texture Scale##Sprite", glm::value_ptr(cubeSprite->textureScale), 0.1f);
	ImGui::DragFloat4("Texture Rect##Sprite", &cubeSprite->textureRect.x, 0.1f);
	ImGui::ColorPicker4("Color##Sprite", glm::value_ptr(m_cube->GetComponent<SpriteRenderer>()->color));

	if (ImGui::Button("Reset"))
	{
		ResetScene();
	}

	auto stats = GameEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.drawCalls);
	ImGui::Text("Quads: %d", stats.quadCount);
	ImGui::Text("Vertices: %d", stats.vertexCount);
	ImGui::Text("Indices: %d", stats.indexCount);
	ImGui::Text("Max Texture Slots Used: %d", stats.maxTextureSlotsUsed);
}

void MainLayer::CreateScene()
{
	GE_PROFILE_FUNCTION();

	// --- player
	
	//m_player = CreateGameObject({
	//	std::static_pointer_cast<Component>(MakeRef<RectMaterial>())
	//});

	m_player = CreateGameObject();

	m_characterSprite = m_player->AddComponent<Sprite>();
	m_characterSprite->texture = GameEngine::Texture2D::Create("./res/textures/red-hood-character-sheet.png");
	m_characterSprite->texture->SetFilter(GameEngine::Texture::Filter::Nearest);

	m_characterSpriteAnimator = m_player->AddComponent<SpriteAnimator>();

	Ref<Texture2D> texture = GameEngine::Texture2D::Create("./res/textures/red-hood-character-sheet.png");
	texture->SetFilter(GameEngine::Texture::Filter::Nearest);
	TextureAtlas textureAtlas = TextureAtlas(c_characterSheetNumCells[0], c_characterSheetNumCells[1], texture);
	m_characterSpriteAnimator->SetTextureAtlas(textureAtlas);

	m_player->GetTransform()->zIndex = 0.2f;
	m_player->GetTransform()->size = { 2.0f, 2.0f };

	// --- cube
	
	m_cube = CreateGameObject();
	m_cube->AddComponent<SpriteRenderer>();
	auto cubeMaterial = m_cube->AddComponent<Sprite>();
	cubeMaterial->texture = GameEngine::Texture2D::Create("./res/textures/checkerboard.png");

	// --- editor camera

	m_editorCamera = CreateGameObject();
	m_cameraController = m_editorCamera->AddComponent<CameraController2D>();
}

void MainLayer::ResetScene()
{
	GE_PROFILE_FUNCTION();

	// ---- player
	m_player->GetTransform()->position = { 0.0f, 0.0f };

	m_characterAnimationIndex = 0;

	m_characterSpriteAnimator->framesPerSec = 30.0f;
	m_characterSpriteAnimator->startFrame = { 0, 0 };
	m_characterSpriteAnimator->numFrames = c_characterSheetNumCells[0];

	// --- editor camera
	m_cameraController->SetZoom(1.0f);
	m_cameraController->SetPosition({ 0.0f, 0.0f });
}

#include "MainLayer.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Components/Player.h"

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

	if (m_followPlayer)
		m_cameraController->SetPosition(m_player->GetTransform()->position);

	GameEngine::Renderer2D::EndScene();
}

void MainLayer::OnImGuiUpdate()
{
	GE_PROFILE_FUNCTION();

	Layer::OnImGuiUpdate();

	Ref<Sprite> cubeSprite = m_background->GetComponent<Sprite>();

	ImGui::Text("Camera");
	ImGui::Checkbox("Follow Player", &m_followPlayer);

	ImGui::Text("Grass Texture");
	ImGui::DragFloat("Scale##Sprite", &cubeSprite->textureScale.y, 0.1f);
	//ImGui::DragFloat4("Texture Rect##Sprite", &cubeSprite->textureRect.x, 0.1f);
	ImGui::ColorPicker4("Color##Sprite", glm::value_ptr(m_background->GetComponent<SpriteRenderer>()->color));

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

	m_playerObject = CreateGameObject();
	m_player = m_playerObject->AddComponent<Player>();

	//m_characterSprite = m_playerObject->AddComponent<Sprite>();
	//m_characterSprite->texture = GameEngine::Texture2D::Create("./res/textures/red-hood-character-sheet.png");
	//m_characterSprite->texture->SetFilter(GameEngine::Texture::Filter::Nearest);


	m_playerObject->GetTransform()->zIndex = 0.2f;
	m_playerObject->GetTransform()->size = { 1.0f, 1.0f };

	// --- background
	m_background = CreateGameObject();
	m_background->GetTransform()->size = { 10.0f, 10.0f };
	m_background->AddComponent<SpriteRenderer>();
	auto cubeMaterial = m_background->AddComponent<Sprite>();
	cubeMaterial->texture = GameEngine::Texture2D::Create("./res/textures/grass.png");

	// --- editor camera

	m_editorCamera = CreateGameObject();
	m_cameraController = m_editorCamera->AddComponent<CameraController2D>();
}

void MainLayer::ResetScene()
{
	GE_PROFILE_FUNCTION();

	// ---- player
	m_playerObject->GetTransform()->position = { 0.0f, 0.0f };
	m_player->Reset();

	// --- background
	Ref<Sprite> backgroundSprite = m_background->GetComponent<Sprite>();
	Ref<SpriteRenderer> backgroundSpriteRenderer = m_background->GetComponent<SpriteRenderer>();
	backgroundSprite->textureScale = { 1.0f, -40.0f };
	backgroundSpriteRenderer->color = { 0.8f, 0.8f, 0.8f, 1.0f };

	// --- editor camera
	m_cameraController->SetZoom(1.0f);
	m_cameraController->SetPosition({ 0.0f, 0.0f });

	m_followPlayer = true;
}

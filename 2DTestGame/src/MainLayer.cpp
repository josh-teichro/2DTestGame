#include "MainLayer.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

MainLayer::MainLayer() : 
	m_cameraController(1.0f)
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

	Layer::OnUpdate();

	float deltaTime = GameEngine::Time::GetDeltaTime();

	m_cameraController.OnUpdate();

	// red hood character
	m_characterAnimationTime += deltaTime;
	while (m_characterAnimationTime > 1 / m_characterAnimationSpeed)
	{
		m_characterAnimationFrameIndex = (m_characterAnimationFrameIndex + 1) % (int)c_characterSheetNumCells[1];
		m_characterAnimationTime -= 1 / m_characterAnimationSpeed;
	}

	GameEngine::RectTexture& characterTexture = m_characterMaterial->texture;
	characterTexture.textureCoords[0] = glm::vec2(m_characterAnimationFrameIndex, m_characterAnimationIndex) / c_characterSheetNumCells;
	characterTexture.textureCoords[1] = glm::vec2(m_characterAnimationFrameIndex + 1, m_characterAnimationIndex + 1) / c_characterSheetNumCells;

	// draw scene
	GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	GameEngine::RenderCommand::Clear();

	GameEngine::Renderer2D::ResetStats();
	GameEngine::Renderer2D::BeginScene(m_cameraController.GetCamera());

	// draw character
	GameEngine::Renderer2D::DrawRect(*m_player->GetTransform(), *m_characterMaterial);

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
		for (int i = 0; i < (int)c_characterSheetNumCells[0]; i++)
		{
			bool is_selected = (m_characterAnimationIndex == i);
			if (ImGui::Selectable(std::to_string(i).c_str(), is_selected)) {
				m_characterAnimationIndex = i;
				m_characterAnimationFrameIndex = 0;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();  
		}
		ImGui::EndCombo();
	}
	ImGui::DragFloat("Animation Speed", &m_characterAnimationSpeed, 1.0f, 0.0f, 60.0f);

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

bool MainLayer::OnEvent(const GameEngine::Event& e)
{
	GE_PROFILE_FUNCTION();

	bool result = false;
	result |= m_cameraController.OnEvent(e);
	result |= HandlesEvents::OnEvent(e);
	return result;
}

bool MainLayer::OnKeyUp(const GameEngine::KeyUpEvent& e)
{
	return false;
}

void MainLayer::CreateScene()
{
	GE_PROFILE_FUNCTION();

	//m_player = CreateGameObject({
	//	std::static_pointer_cast<Component>(MakeRef<RectMaterial>())
	//});

	m_player = CreateGameObject();

	m_characterMaterial = m_player->AddComponent<RectMaterial>();
	m_characterMaterial->texture.baseTexture = GameEngine::Texture2D::Create("./res/textures/red-hood-character-sheet.png");
	m_characterMaterial->texture.baseTexture->SetFilter(GameEngine::Texture::Filter::Nearest);

	m_player->GetTransform()->zIndex = 0.2f;
	m_player->GetTransform()->size = { 2.0f, 2.0f };
}

void MainLayer::ResetScene()
{
	GE_PROFILE_FUNCTION();

	m_cameraController.SetZoom(1.0f);
	m_cameraController.SetPosition({ 0.0f, 0.0f });

	m_characterAnimationIndex = 9;
	m_characterAnimationFrameIndex = 0;
	m_characterAnimationSpeed = 30;
	m_characterAnimationTime = 0.0f;
	m_player->GetTransform()->position = { 0.0f, 0.0f };
}

#include "TestGame2D.h"
#include "MainLayer.h"

#include <GameEngine/Core/EntryPoint.h>

/**
* Sandbox.
*/
TestGame2D::TestGame2D()
{
	PushLayer(new MainLayer());
}

TestGame2D::~TestGame2D()
{
}

GameEngine::Application* GameEngine::CreateApplication() {
	return new TestGame2D();
}

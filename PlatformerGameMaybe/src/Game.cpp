#include "Game.h"

Game::Game()
{
	renderer.Init();

	Entity box = CreateEntity();
	box.AddComponent<RenderableComponent>();
	box.GetComponent<RenderableComponent>().Color = glm::vec3(181.f/255.f, 53.f/255.f, 49.f/255.f);
	box.GetComponent<TransformComponent>().Position = glm::vec3(500, 400.25f, 0.0f);

	camera = CreateEntity();
	camera.AddComponent<CameraComponent>();
	camera.GetComponent<TransformComponent>().Position.z = -2;
}

Game::~Game()
{
}

void Game::Render()
{
	renderer.Render(&m_registry);
}

void Game::Update(float dt)
{
	// CameraComponent& cameraComponent = camera.GetComponent<CameraComponent>();
	// TransformComponent& cameraTransform = camera.GetComponent<TransformComponent>();
	// glm::vec3 forward = glm::normalize(glm::inverse(cameraComponent.View)[2]);
	// glm::vec3 right = glm::normalize(glm::inverse(cameraComponent.View)[0]);
	// glm::vec3 up = glm::normalize(glm::inverse(cameraComponent.View)[1]);
}


void Game::FixedUpdate(float dt)
{
	
}

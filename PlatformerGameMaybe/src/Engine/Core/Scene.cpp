#include "Scene.h"
#include "Entity.h"

Scene::Scene()
{
	m_glfwWindow = Window::CreateWindowAndInit(WINDOW_WIDTH, WINDOW_HEIGHT, "Phy");
}

Scene::~Scene()
{
	glfwTerminate();
}

void Scene::Run()
{
	float previous = (float)glfwGetTime();
	float secsPerUpdate = 1.0f / 60.0f;
	float steps = 0.f;

	while (Window::WindowIsOpen(m_glfwWindow))
	{
		Window::Clear();

		float now = (float)glfwGetTime();
		float elapsed = now - previous;
		previous = now;
		steps += elapsed;

		while (steps >= secsPerUpdate)
		{
			FixedUpdate(elapsed);
			steps -= secsPerUpdate;
		}

		Update(elapsed);
		Render();

		KeyListener::EndFrame();
		MouseListener::EndFrame();
		Window::EndFrame(m_glfwWindow);
	}
}

Entity Scene::CreateEntity()
{
	Entity entity = { m_registry.create(), this };
	entity.AddComponent<TransformComponent>();
	return entity;
}

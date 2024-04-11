#include "Editor.h"

Editor::Editor()
{
	Entity box = CreateEntity();
	box.AddComponent<RenderableComponent>();
	box.GetComponent<RenderableComponent>().Color = glm::vec3(181.f / 255.f, 53.f / 255.f, 49.f / 255.f);
	box.GetComponent<TransformComponent>().Position = glm::vec3(500, 400.25f, 0.0f);
	box.AddComponent<RigidbodyComponent>();
	box.AddComponent<BoxColliderComponent>();

	Entity ground = CreateEntity();
	ground.AddComponent<RenderableComponent>();
	ground.GetComponent<RenderableComponent>().Color = glm::vec3(0.f, 1.f, 0.f);
	ground.GetComponent<TransformComponent>().Position = glm::vec3(500.f, 100.f, 0.f);
	ground.GetComponent<TransformComponent>().Scale = glm::vec3(500.f, 61.f, 0.f);
	ground.AddComponent<StaticbodyComponent>();
	ground.AddComponent<BoxColliderComponent>();
	ground.GetComponent<BoxColliderComponent>().sizeX = 3.f;
	ground.GetComponent<BoxColliderComponent>().sizeY = .3f;

	m_world = new b2World(b2Vec2(0.f, -10.f));

	renderer.Init();

	m_camera = CreateEntity();
	m_camera.AddComponent<CameraComponent>();
	m_camera.GetComponent<TransformComponent>().Position.z = -2;

	m_box2dMgr.Init(m_world, &m_registry);
}

Editor::~Editor()
{
}

void Editor::Render()
{
	renderer.Render(&m_registry);
}

void Editor::Update(float dt)
{
	TransformComponent& camTrans = m_camera.GetComponent<TransformComponent>();
	if (MouseListener::GetMouseButtonPressed(0))
	{
		camTrans.Position.x -= 1000 * MouseListener::GetDx() * dt;
		camTrans.Position.y += 1000 * MouseListener::GetDy() * dt;
	}
}

void Editor::FixedUpdate(float dt)
{
	m_world->Step(1.f / 60.f, 5, 2);

	m_box2dMgr.Update();
}

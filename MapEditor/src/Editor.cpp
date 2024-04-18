#include "Editor.h"

Editor::Editor()
{
	m_renderer.Init();
	m_objPlacer.Init();

	m_camera = CreateEntity();
	m_camera.AddComponent<CameraComponent>();
	m_camera.GetComponent<TransformComponent>().Position.z = -2;
}

Editor::~Editor()
{
}

void Editor::Render()
{
	m_renderer.Render(&m_registry);
}

void Editor::Update(float dt)
{
	TransformComponent& camTrans = m_camera.GetComponent<TransformComponent>();
	if (MouseListener::GetMouseButtonPressed(2))
	{
		camTrans.Position.x -= 1000 * MouseListener::GetDx() * dt;
		camTrans.Position.y += 1000 * MouseListener::GetDy() * dt;
	}

	glm::vec2 camPos(camTrans.Position.x, camTrans.Position.y);
	m_objPlacer.Update(&m_registry, this, camPos);
}

void Editor::FixedUpdate(float dt)
{
}

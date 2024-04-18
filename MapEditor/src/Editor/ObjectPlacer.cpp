#include "ObjectPlacer.h"

void Print(const glm::vec2& vec)
{
	std::cout << "X: " << vec.x << ", Y: " << vec.y << "\n";
}

void ObjectPlacer::Update(entt::registry* reg, Scene* scene, const glm::vec2& camPos)
{
	if (MouseListener::GetMouseButtonClicked(0))
	{
		glm::vec2& mousePos = ScreenToWorld(MouseListener::GetX(), MouseListener::GetY(), camPos);

		// snap to grid
		int gridSize = 100;
		float x = floor(mousePos.x / gridSize) * gridSize + gridSize / 2;
		float y = floor(mousePos.y / gridSize) * gridSize + gridSize / 2;

		Entity entity = { reg->create(), scene };
		entity.AddComponent<TransformComponent>().Position = glm::vec3(x, y, 0.f);
		entity.AddComponent<RenderableComponent>();
	}
}

glm::vec2 ObjectPlacer::ScreenToWorld(float screenX, float screenY, const glm::vec2& camPos)
{
	return glm::vec2(screenX, WINDOW_HEIGHT - screenY) - camPos;
}

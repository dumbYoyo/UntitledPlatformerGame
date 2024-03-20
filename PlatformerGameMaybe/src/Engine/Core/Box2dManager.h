#pragma once

#include <entt/entt.hpp>
#include "Components.h"
#include "Globals.h"

class Box2dManager
{
public:
	void Init(b2World* world, entt::registry* reg);
	void Update();
private:
	b2World* m_world;
	entt::registry* m_registry;
	glm::vec2 ScreenToWorld(float screenX, float screenY);
	glm::vec2 WorldToScreen(float worldX, float worldY);
};

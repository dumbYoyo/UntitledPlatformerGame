#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "Engine/GLobals.h"
#include "Engine/Entity.h"
#include "Engine/MouseListener.h"
#include <entt/entt.hpp>
#include <cmath>
#include <Engine/Globals.h>

class ObjectPlacer
{
public:
	void Update(entt::registry* reg, Scene* scene, const glm::vec2& camPos);
private:
	glm::vec2 ScreenToWorld(float screenX, float screenY, const glm::vec2& camPos);
};
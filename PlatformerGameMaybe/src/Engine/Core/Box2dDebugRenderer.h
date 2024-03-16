#pragma once

#include <box2d/box2d.h>
#include <entt/entt.hpp>
#include "Shader.h"
#include "Components.h"

class Box2dDebugRenderer
{
public:
	void Init(entt::registry* reg);
	void Render(const b2Vec2* vertices, int32 vertexCount);
private:
	Shader shader;
	entt::registry* m_registry;
	unsigned int m_vao = 0, m_vbo = 0, m_ibo = 0;
};
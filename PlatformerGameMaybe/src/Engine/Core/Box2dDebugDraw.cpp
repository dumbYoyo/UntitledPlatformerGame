#include "Box2dDebugDraw.h"

Box2dDebugDraw::Box2dDebugDraw(entt::registry* reg)
{
	m_box2dRenderer.Init(reg);
}

void Box2dDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	m_box2dRenderer.Render(vertices, vertexCount);
}

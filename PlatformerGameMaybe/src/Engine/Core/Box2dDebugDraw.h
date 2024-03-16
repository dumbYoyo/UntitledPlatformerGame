#pragma once

#include <box2d/box2d.h>
#include "Box2dDebugRenderer.h"

class Box2dDebugDraw : public b2Draw
{
public:
	Box2dDebugDraw(entt::registry* reg);

	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
	virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {}
	virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {}
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
	virtual void DrawTransform(const b2Transform& xf) {}
	virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) {}
private:
	Box2dDebugRenderer m_box2dRenderer;
};
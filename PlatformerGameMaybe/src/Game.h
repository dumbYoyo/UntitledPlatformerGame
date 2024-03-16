#pragma once

#include <box2d/box2d.h>
#include "Engine/Core/Window.h"
#include "Engine/Core/Components.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Scene.h"
#include "Engine/Core/Box2dDebugRenderer.h"
#include "Engine/Core/Box2dDebugDraw.h"

class Game : public Scene
{
public:
	Game();
	virtual ~Game();

	void Render() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
private:
	Renderer m_renderer;
	Entity m_camera;
	Box2dDebugDraw* m_box2dDebugDraw;
	b2World* m_world;
	
	float GravityAccl = 100.f;
};
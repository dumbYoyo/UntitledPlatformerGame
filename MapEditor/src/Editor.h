#pragma once

#include "Engine/Scene.h"
#include "Engine/Entity.h"
#include "Engine/Renderer.h"
#include "Engine/Box2dManager.h"

class Editor : public Scene
{
public:
	Editor();
	~Editor();

	virtual void Render() override;
	virtual void Update(float dt) override;
	virtual void FixedUpdate(float dt) override; 
private:
	b2World* m_world;

	Renderer renderer;
	Entity m_camera;
	Box2dManager m_box2dMgr;
};
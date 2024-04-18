#pragma once

#include "Engine/Scene.h"
#include "Engine/Entity.h"
#include "Engine/Renderer.h"
#include "Engine/Box2dManager.h"
#include "Editor/ObjectPlacer.h"

class Editor : public Scene
{
public:
	Editor();
	~Editor();

	virtual void Render() override;
	virtual void Update(float dt) override;
	virtual void FixedUpdate(float dt) override; 
private:
	Renderer m_renderer;
	ObjectPlacer m_objPlacer;

	Entity m_camera;
};
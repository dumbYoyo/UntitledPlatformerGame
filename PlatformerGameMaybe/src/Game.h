#pragma once

#include "Engine/Core/Window.h"
#include "Engine/Core/Components.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Scene.h"

class Game : public Scene
{
public:
	Game();
	virtual ~Game();

	void Render() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
private:
	Renderer renderer;
	Entity camera;
	
	float GravityAccl = 100.f;
};
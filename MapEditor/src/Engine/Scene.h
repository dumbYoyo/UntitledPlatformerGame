#pragma once

#include "Window.h"
#include "Components.h"
#include <entt/entt.hpp>
#include "Globals.h"

class Entity;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	void Run();
	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
	virtual void FixedUpdate(float dt) = 0; // don't take inputs here
	Entity CreateEntity();
protected:
	GLFWwindow* m_glfwWindow;
	entt::registry m_registry;

	friend class Entity;
};

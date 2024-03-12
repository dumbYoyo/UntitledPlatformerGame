#pragma once

#include "Window.h"
#include "Components.h"
#include <entt/entt.hpp>

class Entity;

class Scene
{
public:
	static const unsigned int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;

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

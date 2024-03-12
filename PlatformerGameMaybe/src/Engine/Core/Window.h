#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MouseListener.h"
#include "KeyListener.h"

namespace Window {

	static GLFWwindow* CreateWindowAndInit(int width, int height, const char* title, GLFWmonitor* monitor = 0)
	{
		glfwInit();

		GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello World", 0, 0);

		glfwMakeContextCurrent(window);
		gladLoadGL();

		glfwSetKeyCallback(window, KeyListener::KeyCallback);
		glfwSetMouseButtonCallback(window, MouseListener::MouseButtonCallback);
		glfwSetCursorPosCallback(window, MouseListener::MousePosCallback);
		glfwSetScrollCallback(window, MouseListener::MouseScrollCallback);

		glfwSwapInterval(0);

		return window;
	}

	static bool WindowIsOpen(GLFWwindow* window)
	{
		return !glfwWindowShouldClose(window);
	}

	static void Clear()
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	static void EndFrame(GLFWwindow* window)
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	static void DisableCursor(GLFWwindow* window)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	static void EnableCursor(GLFWwindow* window)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}
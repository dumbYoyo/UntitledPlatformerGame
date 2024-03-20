#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>
#include "KeyListener.h"
#include "MouseListener.h"
#include <box2d/box2d.h>

struct TransformComponent
{
	glm::vec3 Position = glm::vec3(0, 0, 0);
	glm::vec3 Rotation = glm::vec3(0, 0, 0); // in deg
	glm::vec3 Scale = glm::vec3(100, 100, 100);
};

struct CameraComponent
{
	glm::vec3 LookPosition{ 0, 0, 0 };
	glm::vec3 Up{ 0, 1, 0 };
	glm::mat4 View = glm::mat4(1.0f);

	glm::mat4& GenerateAndGetViewMatrix(const TransformComponent& cameraTransform)
	{
		View = glm::mat4(1.0f);
		View = glm::rotate(View, glm::radians(cameraTransform.Rotation.x), glm::vec3(1, 0, 0));
		View = glm::rotate(View, glm::radians(cameraTransform.Rotation.y), glm::vec3(0, 1, 0));
		View = glm::rotate(View, glm::radians(cameraTransform.Rotation.z), glm::vec3(0, 0, 1));
		View = glm::translate(View, cameraTransform.Position);
		return View;
	}
};

class RenderableComponent
{
public:
	unsigned int Vao = 0;
	unsigned int TextureId = 0;
	std::string TexturePath;
	unsigned int NumVertices;
	glm::vec3 Color = glm::vec3(1, 1, 1);

	RenderableComponent()
	{
		float vertices[] = {
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
		};
		float texCoords[] = {
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};
		int indices[] = {
			 0, 1, 2, 2, 3, 0
		};

		NumVertices = sizeof(indices) / sizeof(int);

		glGenVertexArrays(1, &Vao);
		glBindVertexArray(Vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &m_tbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_tbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void SetTexture(std::string texPath)
	{
		TexturePath = texPath;

		glGenTextures(1, &TextureId);
		glBindTexture(GL_TEXTURE_2D, TextureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, channels;
		unsigned char* data = stbi_load(texPath.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "ERROR::TEXTURE_LOADING::" << texPath << "\n";
		}
	}
	unsigned int m_vbo = 0;
private:
	unsigned int m_tbo = 0;
	unsigned int m_ibo = 0;
};

struct BoxColliderComponent
{
	float sizeX = 0.5f;
	float sizeY = 0.5f;
};

struct RigidbodyComponent
{
	b2Body* body;
};

struct StaticbodyComponent
{
	b2Body* body;
};

#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int Id;

	void Init(const char* vertexPath, const char* fragmentPath);
	void Bind();
	void Unbind();
	void LoadMat4f(const char* uniformName, const glm::mat4& data);
	void LoadInt(const char* uniformName, int data);
	void LoadVec3(const char* uniformName, const glm::vec3& data);
	void CleanUp();
private:
	std::string ReadShaderFile(const char* filePath);
};
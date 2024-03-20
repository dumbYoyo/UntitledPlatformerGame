#pragma once

#include <entt/entt.hpp>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Components.h"
#include "Shader.h"
#include "Entity.h"
#include "Globals.h"

class Renderer
{
public:
	void Init();
	void Render(entt::registry* reg);
private:
	void Update(entt::registry* reg);
	void Draw(entt::registry* reg);
	std::unordered_map<std::string, std::vector<entt::entity>> m_sortedEntityIds; // key:value = texPath: ids (entity)
	Shader m_entityShader;
	Shader* m_crntShader;
};

#include "Renderer.h"

void Renderer::Init()
{
	m_entityShader.Init("res/vertex.glsl", "res/fragment.glsl");
	m_crntShader = &m_entityShader;

	glm::mat4 proj = glm::ortho(0.f, 1280.f, 0.f, 720.f, 0.1f, 100.f);
	m_entityShader.Bind();
	m_entityShader.LoadMat4f("proj", proj);
	m_entityShader.Unbind();
}

void Renderer::Update(entt::registry* reg)
{
	m_sortedEntityIds.clear();

	auto view = reg->view<RenderableComponent, TransformComponent>();
	for (auto entity : view)
	{
		RenderableComponent& renderable = view.get<RenderableComponent>(entity);
		auto itr = m_sortedEntityIds.find(renderable.TexturePath);
		if (itr != m_sortedEntityIds.end())
		{
			itr->second.push_back(entity);
		}
		else
		{
			std::vector<entt::entity> entities;
			entities.push_back(entity);
			m_sortedEntityIds.insert(std::make_pair(renderable.TexturePath, entities));
		}
	}
}

void Renderer::Draw(entt::registry* reg)
{
	auto view = reg->view<RenderableComponent, TransformComponent>();
	for (auto kv : m_sortedEntityIds)
	{
		std::string texPath = kv.first;
		auto it = m_sortedEntityIds.find(texPath);
		std::vector<entt::entity> batch = it->second;
		entt::entity commonEntity = batch.front();
		RenderableComponent& commonRenderable = view.get<RenderableComponent>(commonEntity);

		int hasTex = commonRenderable.TexturePath.empty() ? 0 : 1;
		m_crntShader->LoadInt("hasTex", hasTex);

		if (hasTex)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, commonRenderable.TextureId);
			m_crntShader->LoadInt("texSampler", 0);
		}

		glBindVertexArray(commonRenderable.Vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		for (auto entity : batch)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);

			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, transform.Position);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.f));
			modelMatrix = glm::scale(modelMatrix, transform.Scale);
			m_crntShader->LoadMat4f("model", modelMatrix);

			RenderableComponent& renderable = view.get<RenderableComponent>(entity);
			m_crntShader->LoadVec3("objColor", renderable.Color);

			glDrawElements(GL_TRIANGLES, commonRenderable.NumVertices, GL_UNSIGNED_INT, 0);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glBindVertexArray(0);
	}
}

void Renderer::Render(entt::registry* reg)
{
	Update(reg);

	m_crntShader->Bind();

	auto cameraView = reg->view<TransformComponent, CameraComponent>();
	for (auto entity : cameraView)
	{
		TransformComponent& cameraTransfrom = cameraView.get<TransformComponent>(entity);
		CameraComponent& cameraComponent = cameraView.get<CameraComponent>(entity);
		cameraComponent.View = glm::mat4(1.0f);
		cameraComponent.View = glm::rotate(cameraComponent.View, glm::radians(cameraTransfrom.Rotation.x), glm::vec3(1, 0, 0));
		cameraComponent.View = glm::rotate(cameraComponent.View, glm::radians(cameraTransfrom.Rotation.y), glm::vec3(0, 1, 0));
		cameraComponent.View = glm::rotate(cameraComponent.View, glm::radians(cameraTransfrom.Rotation.z), glm::vec3(0, 0, 1));
		cameraComponent.View = glm::translate(cameraComponent.View, cameraTransfrom.Position);
		m_crntShader->LoadMat4f("view", cameraComponent.View);
	}

	Draw(reg);

	m_crntShader->Unbind();
}

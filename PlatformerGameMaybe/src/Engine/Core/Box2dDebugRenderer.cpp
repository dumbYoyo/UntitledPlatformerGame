#include "Box2dDebugRenderer.h"

void Box2dDebugRenderer::Init(entt::registry* reg)
{
	m_registry = reg;
	shader.Init("res/box2dDebugDraw/vertex.glsl", "res/box2dDebugDraw/fragment.glsl");

	glm::mat4 proj = glm::ortho(0.f, BOX2D_RENDERER_VIEWPORT_WIDTH, 0.f, BOX2D_RENDERER_VIEWPORT_HEIGHT, 0.1f, 100.f);
	shader.Bind();
	shader.LoadMat4f("proj", proj);
	shader.Unbind();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	int indices[] = {
		0, 1, 2, 2, 3, 0,
	};

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Box2dDebugRenderer::Render(const b2Vec2* vertices, int32 vertexCount)
{
	float vertexData[] = {
		vertices[0].x, vertices[0].y, 0.f,
		vertices[1].x, vertices[1].y, 0.f,
		vertices[2].x, vertices[2].y, 0.f,
		vertices[3].x, vertices[3].y, 0.f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexData), vertexData);

	shader.Bind();

	auto cameraView = m_registry->view<TransformComponent, CameraComponent>();
	for (auto entity : cameraView)
	{
		TransformComponent& cameraTransfrom = cameraView.get<TransformComponent>(entity);
		CameraComponent& cameraComponent = cameraView.get<CameraComponent>(entity);
		shader.LoadMat4f("view", cameraComponent.GenerateAndGetViewMatrix(cameraTransfrom));
	}

	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(BOX2D_RENDERER_SCALE_X, BOX2D_RENDERER_SCALE_Y, 1.f));
	shader.LoadMat4f("model", modelMatrix);

	shader.LoadVec3("objColor", glm::vec3(1, 1, 1));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.Unbind();
}

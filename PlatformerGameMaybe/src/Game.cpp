#include "Game.h"

b2Body* body;
b2Body* groundBody;

b2Vec2 ScreenToWorld(float screenX, float screenY)
{
	float w = float(1280);
	float h = float(720);
	float u = screenX / w;
	float v = (h - screenY) / h;

	b2Vec2 lower = b2Vec2(0, 0);
	b2Vec2 upper = b2Vec2(0, 0);

	b2Vec2 pw;
	pw.x = (1.0f - u) * lower.x + u * upper.x;
	pw.y = (1.0f - v) * lower.y + v * upper.y;
	return pw;
}

Game::Game()
{
	m_renderer.Init();

	Entity box = CreateEntity();
	box.AddComponent<RenderableComponent>();
	box.GetComponent<RenderableComponent>().Color = glm::vec3(181.f/255.f, 53.f/255.f, 49.f/255.f);
	box.GetComponent<TransformComponent>().Position = glm::vec3(500, 400.25f, 0.0f);
	box.AddComponent<RigidbodyComponent>();

	m_camera = CreateEntity();
	m_camera.AddComponent<CameraComponent>();
	m_camera.GetComponent<TransformComponent>().Position.z = -2;
	
	m_box2dDebugDraw = new Box2dDebugDraw(&m_registry);
	m_world = new b2World(b2Vec2(0.f, -10.f));

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(5.f, 5.f);
	body = m_world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.50f, .50f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(5.0f, 1.0f);
	groundBody = m_world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(3.f, .30f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	
	m_world->SetDebugDraw(m_box2dDebugDraw);
	m_box2dDebugDraw->SetFlags(b2Draw::e_shapeBit);
}

Game::~Game()
{
}

void Game::Render()
{
	m_renderer.Render(&m_registry);
	m_world->DebugDraw();
}

void Game::Update(float dt)
{
	// CameraComponent& cameraComponent = camera.GetComponent<CameraComponent>();
	// TransformComponent& cameraTransform = camera.GetComponent<TransformComponent>();
	// glm::vec3 forward = glm::normalize(glm::inverse(cameraComponent.View)[2]);
	// glm::vec3 right = glm::normalize(glm::inverse(cameraComponent.View)[0]);
	// glm::vec3 up = glm::normalize(glm::inverse(cameraComponent.View)[1]);
}


void Game::FixedUpdate(float dt)
{
	m_world->Step(1.f/60.f, 5, 2);
}

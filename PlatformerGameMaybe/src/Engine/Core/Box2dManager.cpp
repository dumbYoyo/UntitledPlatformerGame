#include "Box2dManager.h"

void Box2dManager::Init(b2World* world, entt::registry* reg)
{
	m_world = world;
	m_registry = reg;

	// for rigidbodies
	auto rbView = reg->view<TransformComponent, RigidbodyComponent, BoxColliderComponent>();
	for (auto entity : rbView)
	{
		RigidbodyComponent& rbComponent = reg->get<RigidbodyComponent>(entity);
		TransformComponent& transform = reg->get<TransformComponent>(entity);
		BoxColliderComponent& collider = reg->get<BoxColliderComponent>(entity);

		b2Body* body = rbComponent.body;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		glm::vec2& pos = ScreenToWorld(transform.Position.x, transform.Position.y);
		bodyDef.position.Set(pos.x, pos.y);

		body = world->CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(collider.sizeX, collider.sizeY);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);
	}

	// for staticbodies
	auto sbView = reg->view<TransformComponent, StaticbodyComponent, BoxColliderComponent>();
	for (auto entity : sbView)
	{
		StaticbodyComponent& sbComponent = reg->get<StaticbodyComponent>(entity);
		TransformComponent& transform = reg->get<TransformComponent>(entity);
		BoxColliderComponent& collider = reg->get<BoxColliderComponent>(entity);

		b2Body* body = sbComponent.body;

		b2BodyDef sbDef;
		glm::vec2& pos = ScreenToWorld(transform.Position.x, transform.Position.y);
		sbDef.position.Set(pos.x, pos.y);

		body = world->CreateBody(&sbDef);

		b2PolygonShape sbBox;
		sbBox.SetAsBox(collider.sizeX, collider.sizeY);

		body->CreateFixture(&sbBox, 0.0f);
	}
}

void Box2dManager::Update()
{
	for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		// for rigidbodies
		if (b->GetType() == b2_dynamicBody)
		{
			auto rbView = m_registry->view<TransformComponent, RigidbodyComponent, BoxColliderComponent>();
			for (auto entity : rbView)
			{
				TransformComponent& transform = m_registry->get<TransformComponent>(entity);
				transform.Position = glm::vec3(WorldToScreen(b->GetPosition().x, b->GetPosition().y), 0.f);
			}
		}
	}
}

glm::vec2 Box2dManager::ScreenToWorld(float screenX, float screenY)
{
	float x = screenX * BOX2D_METERS_PER_PIXEL_X;
	float y = screenY * BOX2D_METERS_PER_PIXEL_Y;

	glm::vec2 pw(x, y);

	return pw;
}

glm::vec2 Box2dManager::WorldToScreen(float worldX, float worldY)
{
	float pixelsPerMeterX = 1 / BOX2D_METERS_PER_PIXEL_X;
	float pixelsPerMeterY = 1 / BOX2D_METERS_PER_PIXEL_Y;
	float x = worldX * pixelsPerMeterX;
	float y = worldY * pixelsPerMeterY;
	
	glm::vec2 pw(x, y);

	return pw;
}

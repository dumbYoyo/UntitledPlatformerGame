#pragma once

#include "entt/entt.hpp"
#include "Scene.h"

class Entity
{
public:
	Entity() = default;
	Entity(entt::entity handle, Scene* scene);
	Entity(const Entity& other) = default;

	template<typename T>
	bool HasComponent()
	{
		return m_scene->m_registry.all_of<T>(m_entityHandle);
	}

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		if (HasComponent<T>())
			printf("Entity already has component");

		return m_scene->m_registry.emplace<T>(m_entityHandle, std::forward<Args>(args)...); // see definati of entt's emplace function
	}

	template<typename T>
	T& GetComponent()
	{
		if (!HasComponent<T>())
			printf("Entity does not have component");

		return m_scene->m_registry.get<T>(m_entityHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		if (!HasComponent<T>())
			printf("Entity does not have component");

		m_scene->m_registry.remove<T>(m_entityHandle);
	}

private:
	entt::entity m_entityHandle = entt::null;
	Scene* m_scene = nullptr;
};

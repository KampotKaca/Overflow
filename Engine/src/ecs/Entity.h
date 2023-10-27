#ifndef ENTITY_H
#define ENTITY_H

#include "SceneRuntime.h"
#include "Components.h"
#include "entt.hpp"

namespace overflow
{
	class Entity
	{
	public:
		Entity(entt::entity entity, SceneRuntime* scene);
		~Entity() = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			CORE_ASSERT(!HasComponent<T>(), "Entity already has the component")
			return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			CORE_ASSERT(HasComponent<T>(), "Entity doesn't have the component")
			m_Scene->m_Registry.erase<T>(m_Entity);
		}

		template<typename T>
		void ReplaceComponent()
		{ m_Scene->m_Registry.emplace_or_replace<T>(m_Entity); }

		template<typename T>
		T& GetComponent()
		{ return m_Scene->m_Registry.get<T>(m_Entity); }

		template<typename T>
		bool HasComponent()
		{ return m_Scene->m_Registry.any_of<T>(m_Entity); }

		std::string& Name()
		{ return GetComponent<IDComponent>().Name; }

		char* Label()
		{ return &GetComponent<IDComponent>().Name[0]; }

		UUID UUID()
		{ return GetComponent<IDComponent>(); }

		bool IsValid() const { return m_Scene->m_Registry.valid(m_Entity); }

		operator entt::entity() const { return m_Entity; }

	private:
		entt::entity m_Entity;
		SceneRuntime* m_Scene;
	};
}

#endif //ENTITY_H

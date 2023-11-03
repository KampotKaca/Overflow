#ifndef ENTITY_H
#define ENTITY_H

#include "Scene.h"
#include "Components.h"
#include "entt.hpp"

namespace overflow
{
	class Entity
	{
	public:
		Entity(entt::entity entity, Scene* scene);
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
		bool HasComponent() { return m_Scene->m_Registry.any_of<T>(m_Entity); }
		std::string& Name() { return GetComponent<IDComponent>().Name; }
		char* Label() { return &GetComponent<IDComponent>().Name[0]; }

		bool HasParent() { return m_Scene->m_Registry.valid(GetComponent<Transform>().Parent); };
		UUID UUID() { return GetComponent<IDComponent>(); }
		[[nodiscard]] bool IsValid() const
		{ return m_Entity != entt::null && m_Scene != nullptr && m_Scene->m_Registry.valid(m_Entity); }

		operator entt::entity() const { return m_Entity; }
		[[nodiscard]] Scene* GetScene() const { return m_Scene; }

		void SetParent(entt::entity entity);

	private:
		entt::entity m_Entity;
		Scene* m_Scene;
	};
}

#endif //ENTITY_H

#include "pch.h"
#include "Entity.h"

namespace overflow
{
	Entity::Entity(entt::entity entity, Scene *scene)
	: m_Entity(entity), m_Scene(scene)
	{

	}

	void Entity::SetParent(entt::entity entity)
	{
		auto& parent = GetComponent<Transform>().Parent;
		if(m_Scene->m_Registry.valid(parent))
		{
			auto childComp = m_Scene->m_Registry.get<ChildComponent>(parent);
			auto it = std::find_if(childComp.Children.begin(), childComp.Children.end(),
			                       [&](const auto &item)
			                       { return item == parent; });
			if(it != childComp.Children.end()) childComp.Children.erase(it);
		}

		parent = entity;

		if(m_Scene->m_Registry.any_of<ChildComponent>(parent))
		{
			ChildComponent& childComp = m_Scene->m_Registry.get<ChildComponent>(parent);
			childComp.Children.push_back(m_Entity);
		}
		else
		{
			ChildComponent& childComp = m_Scene->m_Registry.emplace<ChildComponent>(parent);
			childComp.Children.push_back(m_Entity);
		}
	}
}
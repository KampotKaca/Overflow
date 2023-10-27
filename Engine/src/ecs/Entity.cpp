#include "pch.h"
#include "Entity.h"

namespace overflow
{
	Entity::Entity(entt::entity entity, SceneRuntime *scene)
	: m_Entity(entity), m_Scene(scene)
	{

	}
}
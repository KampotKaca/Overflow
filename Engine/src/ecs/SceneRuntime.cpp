#include "pch.h"
#include "SceneRuntime.h"
#include "Components.h"
#include "Entity.h"

namespace overflow
{
	SceneRuntime::SceneRuntime()
	{

	}

	Entity SceneRuntime::CreateEntity()
	{
		auto entity = Entity(m_Registry.create(), this);
		entity.AddComponent<IDComponent>();
		entity.AddComponent<Transform>();
		return entity;
	}
}
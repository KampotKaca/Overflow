#include "pch.h"
#include "Scene.h"
#include "Components.h"
#include "Entity.h"

namespace overflow
{
	Scene::Scene()
	{

	}

	Entity Scene::CreateEntity()
	{
		auto entity = Entity(m_Registry.create(), this);
		entity.AddComponent<IDComponent>();
		entity.AddComponent<Transform>();
		return entity;
	}

	void Scene::SubmitForRendering(bool localCamera)
	{
		auto view3d = m_Registry.view<Transform, Render3D>();
		for (auto& entity : view3d)
		{
			auto [transform, render3d] = view3d.get<Transform, Render3D>(entity);
		}

		auto view2d = m_Registry.view<Transform, Render2D>();
		for (auto& entity : view2d)
		{
			auto [transform, render2d] = view2d.get<Transform, Render2D>(entity);
		}
	}
}
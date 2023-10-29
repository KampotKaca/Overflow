#include "pch.h"
#include "SceneRuntime.h"
#include "Components.h"
#include "Entity.h"
#include "rendering/Renderer.h"

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

	void SceneRuntime::SubmitForRendering(bool localCamera)
	{
		auto view3d = m_Registry.view<Transform, Render3D>();
		for (auto& entity : view3d)
		{
			auto [transform, render3d] = view3d.get<Transform, Render3D>(entity);
			Renderer::Submit(Render_Object
			{
				transform,
				render3d.Material,
				render3d.CastShadows
			});
		}

		auto view2d = m_Registry.view<Transform, Render2D>();
		for (auto& entity : view2d)
		{
			auto [transform, render2d] = view2d.get<Transform, Render2D>(entity);
			Renderer::Submit(Render_Object
			{
				transform,
				render2d.Material,
				render2d.CastShadows
			});
		}
	}
}
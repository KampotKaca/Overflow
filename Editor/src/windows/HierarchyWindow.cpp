#include "pch.h"
#include "HierarchyWindow.h"
#include "ecs/Entity.h"

namespace overflow::edit
{
	static void DrawEntity(Entity entity)
	{
		if(ImGui::Selectable(entity.Label(), false))
		{

		}
	}

	void HierarchyWindow::Awake()
	{
	}

	void HierarchyWindow::Draw()
	{
		auto runtime = Engine::GetRuntime();

		if(ImGui::Begin(Name(), &p_IsOpen))
		{
			if(ImGui::CollapsingHeader(runtime->Label()))
			{
				runtime->GetRegistry().each([&](entt::entity id)
				{
					auto entity = Entity{ id, runtime.get() };
					if(!entity.HasParent()) DrawEntity(entity);
				});
			}

			ImGui::End();
		}
	}
}
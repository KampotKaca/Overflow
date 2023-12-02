#include <imgui.h>
#include <imgui_internal.h>
#include "pch.h"
#include "core/EditorUtils.h"
#include "Editor.h"

#include "SceneWindow.h"
#include "rendering/Renderer.h"

namespace overflow::edit
{
	void SceneWindow::Awake()
	{
		m_Buffer = make_ref(FrameBuffer, FBSpecification::Default());
		m_Camera = Editor::GetCamera();
	}

	void SceneWindow::Draw()
	{
		if(ImGui::Begin(Name(), &p_IsOpen))
		{
			bool isHovered = ImGui::IsWindowHovered();
			
			if(isHovered) ImGui::SetKeyOwner(ImGuiMod_Alt, ImGui::GetCurrentWindow()->ID);

			m_Camera->Update();

			auto newSize = ImGui::GetContentRegionAvail();
			if(newSize != m_Size)
			{
				m_Size = newSize;
				m_Buffer->Resize((int32_t)m_Size.x, (int32_t)m_Size.y);
			}

			Renderer::StartSubmission(Render_Camera
			{
				m_Camera->GetView(),
				m_Camera->GetProjection(m_Size.x / m_Size.y)

			}, m_Buffer);

			Engine::GetRuntime()->SubmitForRendering();

			Renderer::EndSubmission();

			ImGui::Image((void*)(size_t)m_Buffer->GetColorAttachmentRendererID(0),
			             m_Size, { 1, 1 }, { 0, 0 });
			
			ImGui::End();
		}
	}
}
#include "InspectorWindow.h"
#include "pch.h"
#include "HierarchyWindow.h"
#include "core/EditorUtils.h"

namespace overflow::edit
{
	static void TryDrawTransform(Entity entity)
	{
		if(!entity.HasComponent<Transform>()) return;

		ImGui::Separator();
		if(ImGui::CollapsingHeader("Transform"))
		{
			if(ImGui::BeginTable("##__Transform__", 2))
			{
				ImGui::TableSetupColumn("##col_1", ImGuiTableColumnFlags_WidthFixed, 80.0f);
				ImGui::TableSetupColumn("##col_2", ImGuiTableColumnFlags_WidthStretch, 70.0f);

				auto& trs = entity.GetComponent<Transform>();
				edit::DrawVector("Position", trs.Position);
				edit::DrawVector("Rotation", trs.Rotation);
				edit::DrawVector("Scale", trs.Scale, 1);

				ImGui::EndTable();
			}
		}
	}
	static void TryDrawRender3D(Entity entity)
	{
		if(!entity.HasComponent<Render3D>()) return;

		ImGui::Separator();
		if(ImGui::CollapsingHeader("Render3D"))
		{
			if(ImGui::BeginTable("##__Render_3D__", 2))
			{
				ImGui::TableSetupColumn("##col_1", ImGuiTableColumnFlags_WidthFixed, 80.0f);
				ImGui::TableSetupColumn("##col_2", ImGuiTableColumnFlags_WidthStretch, 70.0f);

				auto& r3D = entity.GetComponent<Render3D>();

				edit::Draw_AssetSelection("Mesh", r3D.Mesh);
				edit::Draw_AssetSelection("Material", r3D.Material);
				edit::DrawBool("Shadows", r3D.Shadows);

				ImGui::EndTable();
			}
		}
	}

	void InspectorWindow::Awake()
	{

	}

	void InspectorWindow::Draw()
	{
		if(ImGui::Begin(Name(), &p_IsOpen))
		{
			Entity selection = HierarchyWindow::GetSelection();
			if(selection.IsValid())
			{
				if(ImGui::BeginTable("##__GM__", 2))
				{
					ImGui::TableSetupColumn("##col_1", ImGuiTableColumnFlags_WidthStretch, 80.0f);
					ImGui::TableSetupColumn("##col_2", ImGuiTableColumnFlags_WidthFixed, 120.0f);

					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);

					ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
					ImGui::InputText("##label", selection.Label(), 128);

					ImGui::TableNextColumn();

					auto avail = ImGui::GetContentRegionAvail();
					ImGui::Button("Add Component", { glm::max(5.0f, avail.x - 3), 25 });

					ImGui::EndTable();
				}

				TryDrawTransform(selection);
				TryDrawRender3D(selection);
			}

			ImGui::End();
		}
	}
}
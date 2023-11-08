#include "InspectorWindow.h"
#include "pch.h"
#include "HierarchyWindow.h"
#include "core/EditorUtils.h"

namespace overflow::edit
{
	const uint64_t OPTIONS_ICON = 6611372567339719348;
	static Tex2D* s_Options_Icon;

#define OPTIONS(type) \
	if(ImGui::BeginPopup("Options"))\
	{\
		if(ImGui::Selectable("Remove Component")) entity.RemoveComponent<type>(); \
        ImGui::EndPopup();\
	}

#define COMPONENT_START(type, name) \
    if(!entity.HasComponent<type>()) return;\
	ImGui::Separator();\
	bool isOpen = ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_AllowOverlap);\
	ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetFontSize() - ImGui::GetStyle().ItemSpacing.x);\
    float buttonSize = ImGui::GetFontSize();\
	if(ImGui::ImageButton((ImTextureID)(intptr_t)s_Options_Icon->TexID(), ImVec2{ buttonSize, buttonSize }))\
		ImGui::OpenPopup("Options");

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
				DrawVector("Position", trs.Position);
				DrawVector("Rotation", trs.Rotation);
				DrawVector("Scale", trs.Scale, 1);

				ImGui::EndTable();
			}
		}
	}

	static void TryDrawRender3D(Entity entity)
	{
		COMPONENT_START(Render3D, "Render3D")

		if(isOpen)
		{
			if(ImGui::BeginTable("##__Render_3D__", 2))
			{
				ImGui::TableSetupColumn("##col_1", ImGuiTableColumnFlags_WidthFixed, 80.0f);
				ImGui::TableSetupColumn("##col_2", ImGuiTableColumnFlags_WidthStretch, 70.0f);

				auto& r3D = entity.GetComponent<Render3D>();

				Draw_AssetSelection("Mesh", r3D.Mesh);
				Draw_AssetSelection("Material", r3D.Material);
				DrawBool("Shadows", r3D.Shadows);

				ImGui::EndTable();
			}

			OPTIONS(Render3D)
		}
	}

	static void TryDrawRender2D(Entity entity)
	{
		COMPONENT_START(Render2D, "Render2D")

		if(isOpen)
		{
			if(ImGui::BeginTable("##__Render_2D__", 2))
			{
				ImGui::TableSetupColumn("##col_1", ImGuiTableColumnFlags_WidthFixed, 80.0f);
				ImGui::TableSetupColumn("##col_2", ImGuiTableColumnFlags_WidthStretch, 70.0f);

				auto& r2D = entity.GetComponent<Render2D>();

				Draw_AssetSelection("Texture", r2D.Texture);
				DrawColor("Color", r2D.Color);
				Draw_AssetSelection("Material", r2D.Material);

				ImGui::EndTable();
			}
		}

		OPTIONS(Render2D)
	}

#undef OPTIONS
#undef TRIGGER_OPTIONS

	void InspectorWindow::Awake()
	{
		s_Options_Icon = AssetPipeline::GetTex2D((UUID)OPTIONS_ICON);
		if(s_Options_Icon == nullptr)
		{
			CORE_ERROR("Options Icon asset must exist!!!");
			return;
		}
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
					if(ImGui::Button("Add Component", { glm::max(5.0f, avail.x - 3), 25 }))
						ImGui::OpenPopup("Components");

					if(ImGui::BeginPopup("Components"))
					{
						ImGui::SeparatorText("Components");
						if(!selection.HasComponent<Render2D>() && ImGui::Selectable("Render2D")) selection.AddComponent<Render2D>();
						if(!selection.HasComponent<Render3D>() && ImGui::Selectable("Render3D")) selection.AddComponent<Render3D>();

						ImGui::EndPopup();
					}

					ImGui::EndTable();
				}

				TryDrawTransform(selection);
				TryDrawRender3D(selection);
				TryDrawRender2D(selection);
			}

			ImGui::End();
		}
	}
}
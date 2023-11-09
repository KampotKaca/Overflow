#include "pch.h"
#include "HierarchyWindow.h"

namespace overflow::edit
{
	static Entity m_Selection = Entity(entt::null, nullptr);

	static void DrawEntity(Entity& entity)
	{
		static constexpr float INDENT_SIZE = -15;
		static constexpr float CHILD_INDENT_SIZE = 6;
		static constexpr float ARROW_SIZE = 20;

		static const ImGuiTreeNodeFlags NORMAL_FLAGS =
				ImGuiTreeNodeFlags_OpenOnArrow |
				ImGuiTreeNodeFlags_SpanFullWidth;
		static const ImGuiTreeNodeFlags ZERO_CHILD_FLAGS =
				ImGuiTreeNodeFlags_Leaf |
				ImGuiTreeNodeFlags_SpanFullWidth;

		static const ImGuiMouseButton SELECTION_BUTTON = ImGuiMouseButton_Left;

		ImGuiTreeNodeFlags flags;

		bool hasChildren = entity.HasComponent<ChildComponent>();
		if(hasChildren) flags = NORMAL_FLAGS;
		else flags = ZERO_CHILD_FLAGS;

		if (m_Selection.IsValid() && entity == m_Selection)
			flags |= ImGuiTreeNodeFlags_Selected;

		bool isOpen = ImGui::TreeNodeEx(std::to_string((UUID)entity
				.GetComponent<IDComponent>()).c_str(), flags, "%s", entity.Label());
		if (ImGui::IsItemClicked(SELECTION_BUTTON))
		{
			auto mousePos = ImGui::GetMousePos();
			auto arrowMin = ImGui::GetItemRectMin();

			if (mousePos.x - arrowMin.x > ARROW_SIZE) m_Selection = entity;
		}

		if (isOpen)
		{
			if(hasChildren)
			{
				ImGui::Unindent(CHILD_INDENT_SIZE);

				auto childComp = entity.GetComponent<ChildComponent>();

				for (auto& child : childComp.Children)
				{
					auto ent = Entity(child, entity.GetScene());
					DrawEntity(ent);
				}

				ImGui::Indent(CHILD_INDENT_SIZE);
			}
			ImGui::TreePop();
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
			if(ImGui::CollapsingHeader(runtime->Label(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (auto i = runtime->GetRegistry().storage<entt::entity>().end() - 1;
					i >= runtime->GetRegistry().storage<entt::entity>().begin(); --i)
				{
					auto entity = Entity{ *i, runtime.get() };
					if(!entity.HasParent()) DrawEntity(entity);
				}
			}

			ImGui::End();
		}
	}

	Entity HierarchyWindow::GetSelection() { return m_Selection; }
}
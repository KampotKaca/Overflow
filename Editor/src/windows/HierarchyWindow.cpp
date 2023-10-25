#include "pch.h"
#include "HierarchyWindow.h"

namespace overflow::edit
{
	void HierarchyWindow::Awake()
	{
	}

	void HierarchyWindow::Draw()
	{
		if(ImGui::Begin(Name(), &p_IsOpen))
		{
			ImGui::End();
		}
	}
}
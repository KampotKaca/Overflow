#include "pch.h"
#include "InspectorWindow.h"

namespace overflow::edit
{
	void InspectorWindow::Awake()
	{

	}

	void InspectorWindow::Draw()
	{
		if(ImGui::Begin(Name(), &p_IsOpen))
		{
			ImGui::End();
		}
	}
}
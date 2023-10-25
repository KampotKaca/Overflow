#include "pch.h"
#include "ProjectWindow.h"

namespace overflow::edit
{
	void ProjectWindow::Awake()
	{

	}

	void ProjectWindow::Draw()
	{
		if(ImGui::Begin(Name(), &p_IsOpen))
		{
			ImGui::End();
		}
	}
}
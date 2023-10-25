#include "pch.h"
#include "SceneWindow.h"

namespace overflow::edit
{
	void SceneWindow::Awake()
	{

	}

	void SceneWindow::Draw()
	{
		if(ImGui::Begin(Name(), &p_IsOpen))
		{
			ImGui::End();
		}
	}
}
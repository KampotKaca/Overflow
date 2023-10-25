#include "pch.h"
#include "EditorWindowManager.h"

namespace overflow::edit
{
	std::unordered_map<std::string, ref<EditorWindow>> EditorWindowManager::s_Windows;

	void EditorWindowManager::DrawAll()
	{
		for (auto& win : s_Windows) if(win.second->IsOpen()) win.second->Draw();
	}
}
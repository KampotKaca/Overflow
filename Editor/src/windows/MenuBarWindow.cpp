#include "pch.h"
#include "MenubarWindow.h"
#include "EditorWindowManager.h"

namespace overflow::edit
{
	MenubarWindow::MenubarWindow() = default;
	
	void MenubarWindow::Draw()
	{
		if(ImGui::BeginMainMenuBar())
		{
			if(ImGui::BeginMenu("File"))
			{
				if(ImGui::MenuItem("Save", "Ctrl+S"))
				{
				
				}
				ImGui::EndMenu();
			}
			
			if(!EditorWindowManager::IsEveryWindowOpen())
			{
				if(ImGui::BeginMenu("Windows"))
				{
					for (auto& window : EditorWindowManager::s_Windows)
					{
						if(!window.second->IsOpen() && ImGui::MenuItem(window.second->Name()))
						{
							window.second->Open(true);
						}
					}
					
					ImGui::EndMenu();
				}
			}
			
			ImGui::EndMainMenuBar();
		}
	}
	
	void MenubarWindow::Awake()
	{
	
	}
}
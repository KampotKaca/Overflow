#include "pch.h"
#include "MenubarWindow.h"
#include "EditorWindowManager.h"

#include "Editor.h"
#include "core/FileDialogue.h"

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

				if(ImGui::MenuItem("Open Project", ""))
				{
					auto dialogue = FileDialogue::CreateFileDialogue();
					auto path = dialogue->OpenFolder("Open Project");

					if(Editor::OpenProject(path))
					{
						CORE_INFO("Project Opened!!!");
					}
				}

				if(ImGui::MenuItem("Create Project", ""))
				{
					auto dialogue = FileDialogue::CreateFileDialogue();
					auto path = dialogue->OpenFolder("Create Project");

					if(Editor::CreateProject(path))
					{
						CORE_INFO("Project Created!!!");
					}
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
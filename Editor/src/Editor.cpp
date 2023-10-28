#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "pch.h"

#include "Editor.h"
#include "overflow.h"
#include "EditorWindowManager.h"

#include "windows/MenubarWindow.h"
#include "windows/HierarchyWindow.h"
#include "windows/InspectorWindow.h"
#include "windows/SceneWindow.h"
#include "windows/ProjectWindow.h"

namespace overflow::edit
{
	ref<EditorCamera> Editor::m_Camera = nullptr;
	
	void Editor::Init()
	{
		WindowProps props = WindowProps();
		props.ScaleMode = WindowScaleMode::Maximized;
		props.Title = "Overflow";
		props.IconLocations[0] = RES_PATH;
		props.IconLocations[1] = RES_PATH;

		props.IconLocations[0].append("textures/icons/app/Icon_64.png");
		props.IconLocations[1].append("textures/icons/app/Icon_256.png");

		Engine::Init(props);
		Engine::SetRenderFuncPtr(RenderImGui);

		InitImGui("fonts/noto_sans/Bold.ttf", "fonts/noto_sans/Medium.ttf");
		
		m_Camera = make_ref(EditorCamera);
		
		EditorWindowManager::Create<MenubarWindow>("Menubar");
		EditorWindowManager::Create<HierarchyWindow>("Hierarchy");
		EditorWindowManager::Create<InspectorWindow>("Inspector");
		EditorWindowManager::Create<SceneWindow>("Scene");
		EditorWindowManager::Create<ProjectWindow>("Project");
	}

	void Editor::Run()
	{
		const int target_frame_rate = 60;
		const std::chrono::duration<double> frame_duration(1.0 / target_frame_rate);

		while (Engine::IsRunning())
		{
			auto start_time = std::chrono::high_resolution_clock::now();

			Engine::Update();
			Engine::Render();

			auto end_time = std::chrono::high_resolution_clock::now();
			auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);

			std::chrono::duration<double> sleep_duration = frame_duration - elapsed_time;

			if (sleep_duration > std::chrono::duration<double>(0))
				std::this_thread::sleep_for(sleep_duration);
		}
	}

	int Editor::Terminate()
	{
		Engine::Dispose();

		//ImGui
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		return 0;
	}

	void Editor::InitImGui(const char *font_Bold, const char *font_Regular)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO();
		(void) io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

		io.ConfigWindowsMoveFromTitleBarOnly = true;
		io.ConfigWindowsResizeFromEdges = true;

		std::string regularLoc = RES_PATH;
		std::string boldLoc = RES_PATH;

		regularLoc.append(font_Regular);
		boldLoc.append(font_Bold);

		float fontSize = 18.0f;// *2.0f;
		io.Fonts->AddFontFromFileTTF(boldLoc.c_str(), fontSize);
		io.FontDefault = io.Fonts->AddFontFromFileTTF(regularLoc.c_str(), fontSize);

		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle &style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkThemeColors();

		auto* _root = (GLFWwindow*)Engine::GetWindow()->NativePtr();

		Window::MakeContextCurrent(_root);

		ImGui_ImplGlfw_InitForOpenGL(_root, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void Editor::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

	void Editor::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Editor::End()
	{
		Window* _root = Engine::GetWindow();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)_root->Size().x, (float)_root->Size().y);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			auto* backup_current_context = (GLFWwindow*)Window::GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			Window::MakeContextCurrent(backup_current_context);
		}
	}

	void Editor::RenderImGui()
	{
		Begin();

		ImGui::DockSpaceOverViewport(nullptr);
		EditorWindowManager::DrawAll();

		End();
	}
}
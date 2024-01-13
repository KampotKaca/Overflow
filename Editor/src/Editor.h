#ifndef EDITOR_H
#define EDITOR_H

#include "EditorCamera.h"

namespace overflow::edit
{
	struct Project
	{
		bool IsOpen;
		std::string Path;

		std::string AssetFolder;
		std::string ResourceFolder;
	};

	class Editor
	{
	public:
		static void Init();
		static void Run();
		static int Terminate();

		static ref<EditorCamera> GetCamera() { return s_Camera; }
		static Project GetProject() { return s_Project; }

		static bool IsAnyProjectOpen() { return s_Project.IsOpen; }
		static bool OpenProject(const std::filesystem::path& projectFilePath);
		static bool CreateProject(const std::filesystem::path& projectFilePath);
		static void CloseProject();

	private:
		static void InitImGui(const char *font_Bold, const char *font_Regular);
		static void SetDarkThemeColors();
		static void Begin();
		static void RenderImGui();
		static void End();
		
		static ref<EditorCamera> s_Camera;
		static Project s_Project;
	};
}

#endif //EDITOR_H

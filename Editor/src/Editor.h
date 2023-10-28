#ifndef EDITOR_H
#define EDITOR_H

#include "EditorCamera.h"

namespace overflow::edit
{
	class Editor
	{
	public:
		static void Init();
		static void Run();
		static int Terminate();

		static ref<EditorCamera> GetCamera() { return m_Camera; }
		
	private:
		static void InitImGui(const char *font_Bold, const char *font_Regular);
		static void SetDarkThemeColors();
		static void Begin();
		static void RenderImGui();
		static void End();
		
		static ref<EditorCamera> m_Camera;
	};
}

#endif //EDITOR_H

#ifndef EDITOR_H
#define EDITOR_H

namespace overflow::edit
{
	class Editor
	{
	public:
		static void Init();
		static void Run();
		static int Terminate();

	private:
		static void InitImGui(const char *font_Bold, const char *font_Regular);
		static void SetDarkThemeColors();
		static void Begin();
		static void RenderImGui();
		static void End();
		static void DrawMenubar();
	};
}

#endif //EDITOR_H

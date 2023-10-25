#ifndef ENGINE_H
#define ENGINE_H
#include "core/Window.h"

namespace overflow
{
	class Engine
	{
	public:
		static void Init(const WindowProps& props = WindowProps());

		static void Dispose();
		static void Update();
		static void Render();

		static void Exit() { s_Running = false; }
		static bool IsRunning() { return !s_Window->ShouldClose() && s_Running; }

		static void SetRenderFuncPtr(void (*renderFunc)());
		static Window* GetWindow() { return s_Window; }
	private:
		static Window* s_Window;
		static bool s_Running;
		static void (*s_RenderFunc)();
	};
}

#endif //ENGINE_H
#ifndef ENGINE_H
#define ENGINE_H

#include "core/Window.h"
#include "ecs/SceneRuntime.h"

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
		static ref<SceneRuntime> GetRuntime() { return m_Runtime; }

	private:
		static Window* s_Window;
		static bool s_Running;
		static void (*s_RenderFunc)();
		static ref<SceneRuntime> m_Runtime;
	};
}

#endif //ENGINE_H
#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H
#include "core/utils.h"
#include "core/Window.h"

namespace overflow
{
	class Win_Window : public Window
	{
	public:
		explicit Win_Window(const WindowProps& props);
		~Win_Window() override { glfwDestroyWindow(m_Window); }

		[[nodiscard]] vec2i Size() const override { return m_Data.Size; }

		void SetVSync(VSyncMode mode) override;

		VSyncMode GetVSyncMode() override { return m_Data.SyncMode; }

		[[nodiscard]] bool ShouldClose() const override { return glfwWindowShouldClose(m_Window); }
		[[nodiscard]] void *NativePtr() const override { return m_Window; }

		void BeginDraw() override;
		void EndDraw() override;

	private:
		GLFWwindow* m_Window = nullptr;

//		using EvFunc = std::function<void(Event*)>;

		struct WindowData
		{
			std::string Title;
			vec2i Size;
			VSyncMode SyncMode = VSyncMode::Full;

//			EvFunc EventCallback = nullptr;
		};

		WindowData m_Data;
	};
}

#endif //WIN_WINDOW_H
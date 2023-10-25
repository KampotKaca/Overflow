#include "pch.h"
#include "Window.h"

#if PLATFORM_WINDOWS
#include "platform/windows/Win_Window.h"
#endif

namespace overflow
{
	WindowProps::WindowProps() = default;

	Window* Window::Create(const WindowProps &props)
	{
#ifdef PLATFORM_WINDOWS
		return (Window*)new Win_Window(props);
#elif
		return nullptr;
#endif
	}

	void Window::Terminate()
	{
#ifdef PLATFORM_WINDOWS
		glfwTerminate();
#elif

#endif
	}

	void *Window::GetCurrentContext()
	{
#ifdef PLATFORM_WINDOWS
		return glfwGetCurrentContext();
#elif
		return nullptr;
#endif
	}

	void Window::MakeContextCurrent(void* window)
	{
#ifdef PLATFORM_WINDOWS
		glfwMakeContextCurrent((GLFWwindow*)window);
#elif

#endif
	}
}
#include "pch.h"
#include "Engine.h"

namespace overflow
{
	Window* Engine::s_Window = nullptr;
	bool Engine::s_Running = false;
	void (*Engine::s_RenderFunc)() = nullptr;

	void Engine::Init(const WindowProps& props)
	{
		s_Running = true;
		log::Init();
		s_Window = Window::Create(props);
		CORE_ASSERT(s_Window, "Unable to create window")
	}

	void Engine::Render()
	{
		s_Window->BeginDraw();

		if(s_RenderFunc != nullptr) s_RenderFunc();

		s_Window->EndDraw();
	}

	void Engine::Update()
	{
		s_Window->Update();
	}

	void Engine::Dispose()
	{
		Window::Terminate();
	}

	void Engine::SetRenderFuncPtr(void (*renderFunc)())
	{
		if(s_RenderFunc == nullptr) s_RenderFunc = renderFunc;
		else CORE_ERROR("Trying to set render function ptr twice!!!");
	}
}
#include "pch.h"
#include "Engine.h"
#include "rendering/Renderer.h"
#include "ecs/Entity.h"

namespace overflow
{
	Window* Engine::s_Window = nullptr;
	bool Engine::s_Running = false;
	void (*Engine::s_RenderFunc)() = nullptr;
	ref<Scene> Engine::m_Runtime = nullptr;

	void Engine::Init(const WindowProps& props)
	{
		s_Running = true;
		log::Init();
		s_Window = Window::Create(props);
		CORE_ASSERT(s_Window, "Unable to create window")
		m_Runtime = make_ref(Scene);
		m_Runtime->Name() = "Runtime";
		auto entity = m_Runtime->CreateEntity();
		entity.AddComponent<Render3D>();

		auto entity2 = m_Runtime->CreateEntity();
		auto entity3 = m_Runtime->CreateEntity();
		auto entity4 = m_Runtime->CreateEntity();
		auto entity5 = m_Runtime->CreateEntity();

		entity2.SetParent(entity);
		entity3.SetParent(entity);

		Renderer::RunThread();
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
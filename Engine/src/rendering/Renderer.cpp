#include "pch.h"
#include "Renderer.h"
#include <thread>
#include <mutex>
#include "Engine.h"

namespace overflow
{
	constexpr double FRAME_RATE = 60.0;
	std::mutex mtx;
	
	std::vector<Render_Data> Renderer::m_Data;
	Render_Data Renderer::m_Current;
	std::thread Renderer::m_RenderThread;
	
	void Renderer::StartSubmission(const Render_Camera& camera, const ref<FrameBuffer>& buffer)
	{
		m_Current = Render_Data();
		m_Current.Camera = camera;
		m_Current.Buffer = buffer;
	}
	
	void Renderer::Submit(const Render_Object &object)
	{
		m_Current.Objects.push_back(object);
	}
	
	void Renderer::EndSubmission()
	{
		{
			std::lock_guard<std::mutex> lock(mtx);
			m_Data.push_back(m_Current);
		}
		
		m_Current = Render_Data();
	}
	
	void Renderer::RunThread()
	{
		m_RenderThread = std::thread(ThreadFunction);
		m_RenderThread.detach();
	}
	
	void Renderer::ThreadFunction()
	{
		std::chrono::duration<double> targetDuration = std::chrono::duration<double>(1.0 / FRAME_RATE);
		
		while (Engine::IsRunning())
		{
			auto loopStartTime = std::chrono::high_resolution_clock::now();
			
			Render();
			
			auto loopEndTime = std::chrono::high_resolution_clock::now();
			auto loopDuration = std::chrono::duration_cast<std::chrono::microseconds>(loopEndTime - loopStartTime);
			
			auto sleepDuration = targetDuration - loopDuration;
			if (sleepDuration > std::chrono::microseconds(0))
				std::this_thread::sleep_for(sleepDuration);
		}
	}
	
	void Renderer::Render()
	{
		while(!m_Data.empty())
		{
			auto& data = m_Data[0];
			data.Buffer->Bind();
			data.Buffer->ClearAttachment(1, -1);
			data.Buffer->UnBind();
			m_Data.erase(m_Data.begin());
		}
	}
	
	void Renderer::Dispose()
	{
	
	}
}
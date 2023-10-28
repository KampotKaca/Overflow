#ifndef RENDERER_H
#define RENDERER_H

#include "core/utils.h"
#include "RenderStructure.h"

namespace overflow
{
	class Renderer
	{
	public:
		static void StartSubmission(const Render_Camera& camera, const ref<FrameBuffer>& buffer);
		static void Submit(const Render_Object& object);
		static void EndSubmission();
		static void RunThread();
		static void Dispose();
		
	private:
		static std::vector<Render_Data> m_Data;
		static Render_Data m_Current;
		static std::thread m_RenderThread;
		
		static void ThreadFunction();
		static void Render();
	};
}

#endif //RENDERER_H

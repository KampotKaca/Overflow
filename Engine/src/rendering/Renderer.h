#ifndef RENDERER_H
#define RENDERER_H

#include "core/utils.h"
#include "RenderStructure.h"

namespace overflow
{
	class Renderer
	{
	public:
		static void Init();
		static void StartSubmission(const Render_Camera& camera, const ref<FrameBuffer>& buffer);
		static void Submit(const Render_Object& object);
		static void Submit(const Render2D_Object& object);
		static void EndSubmission();
		static void RunThread();
		static void Dispose();
		static void Render();

	private:
		static std::vector<Render_Data> s_Data;
		static Render_Data s_Current;
		static Shader* s_2DShader;
		static Tex2D* s_DefTex;
//		static std::thread m_RenderThread;
		
		static void ThreadFunction();
	};
}

#endif //RENDERER_H

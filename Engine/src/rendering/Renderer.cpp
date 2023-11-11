#include "pch.h"
#include "Renderer.h"
//#include <thread>
//#include <mutex>
#include "Engine.h"
#include "assets/AssetPipeline.h"

namespace overflow
{
	constexpr double FRAME_RATE = 60.0;
	constexpr uint32_t BUFFER_SIZE_2D = 256;
	constexpr uint32_t VAO_2D_ID = 0, VBO_2D_ID = 0, EBO_2D_ID = 1;
	constexpr int CAMERA_UBO_LOC = 3;
	
	struct Camera_UBO
	{
		mat4 c_View_Projection;
	};
	
	static uint32_t s_CameraUBO;
	static uint32_t s_Arrays[1];
	static uint32_t s_2DBuffers[2];
	
	static uint32_t s_2DIndices[6 * BUFFER_SIZE_2D];
	static uint32_t s_2DVertices[4 * BUFFER_SIZE_2D];
	static mat4 s_2DModel[BUFFER_SIZE_2D];
	static vec4 s_2DColor[BUFFER_SIZE_2D];
	
	static Camera_UBO s_CameraData;
	
	std::mutex mtx;
	
	std::vector<Render_Data> Renderer::s_Data;
	Render_Data Renderer::s_Current;
	Shader* Renderer::s_2DShader = nullptr;
	Tex2D* Renderer::s_DefTex = nullptr;
//	std::thread Renderer::m_RenderThread;
	
	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		
		s_2DShader = AssetPipeline::GetShader((UUID)8743652874635287);
		s_DefTex = AssetPipeline::GetTex2D((UUID)2956874321567890123);
		glGenVertexArrays(1, s_Arrays);
		
		glBindVertexArray(s_Arrays[VAO_2D_ID]);
		glGenBuffers(2, s_2DBuffers);
		
		glBindBuffer(GL_ARRAY_BUFFER, s_2DBuffers[VBO_2D_ID]);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE_2D * 4 * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
		
		for (uint32_t i = 0; i < BUFFER_SIZE_2D; ++i)
		{
			uint32_t base = i * 6;
			
			s_2DIndices[base]     = 0;
			s_2DIndices[base + 1] = 1;
			s_2DIndices[base + 2] = 2;
			
			s_2DIndices[base + 3] = 0;
			s_2DIndices[base + 4] = 2;
			s_2DIndices[base + 5] = 3;
		}
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_2DBuffers[EBO_2D_ID]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, BUFFER_SIZE_2D * 6 * sizeof(uint32_t), s_2DIndices, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		glGenBuffers(1, &s_CameraUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, s_CameraUBO);
		glBufferData(GL_UNIFORM_BUFFER, 16 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		
		glBindBufferRange(GL_UNIFORM_BUFFER, CAMERA_UBO_LOC, s_CameraUBO, 0, 16 * sizeof(float));
	}
	
	void Renderer::StartSubmission(const Render_Camera& camera, const ref<FrameBuffer>& buffer)
	{
		s_Current = Render_Data();
		s_Current.Camera = camera;
		s_Current.Buffer = buffer;
	}
	
	void Renderer::Submit(const Render_Object &object)
	{
		s_Current.Objects.push_back(object);
	}
	
	void Renderer::Submit(const Render2D_Object &object)
	{
		s_Current.Objects2D.push_back(object);
	}
	
	void Renderer::EndSubmission()
	{
		s_Current.SubmissionFinished = true;
		{
			std::lock_guard<std::mutex> lock(mtx);
			s_Data.push_back(s_Current);
		}
		
		s_Current = Render_Data();
	}
	
	void Renderer::RunThread()
	{
//		m_RenderThread = std::thread(ThreadFunction);
//		m_RenderThread.detach();
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
		while(!s_Data.empty())
		{
			auto& data = s_Data[0];
			data.Buffer->Bind();
			data.Buffer->ClearAttachment(1, -1);
			
			glBindVertexArray(s_Arrays[VAO_2D_ID]);
			
			glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, false, sizeof(uint32_t), nullptr);
			glEnableVertexAttribArray(0);
			
			glBindBuffer(GL_UNIFORM_BUFFER, s_CameraUBO);
			
			s_CameraData.c_View_Projection = data.Camera.Projection * data.Camera.View;
			
			glBufferData(GL_UNIFORM_BUFFER, 16 * sizeof(float), &s_CameraData, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			
			for (uint32_t i; i < data.Objects2D.size(); i++)
			{
				for (uint32_t v = 0; v < 4; ++v)
				{
					vec2i uv = vec2i(v / 2, v % 2);

					uint32_t vertexData = 0;
					vertexData |= (i << 20);          // 12 bits instance
					vertexData |= (v << 16);          // 4  bits vertex
					vertexData |= (0 << 8);           // 8  bits texture
					vertexData |= (uv.x << 4);        // 4  bits uvX
					vertexData |= uv.y;               // 4  bits uvY

					s_2DVertices[i * 4 + v] = vertexData;
				}
				
				s_2DModel[i] = data.Objects2D[i].Transform;
				s_2DColor[i] = data.Objects2D[i].Color;
			}
			
			glBindBuffer(GL_UNIFORM_BUFFER, s_2DBuffers[VBO_2D_ID]);
			glBufferData(GL_UNIFORM_BUFFER, BUFFER_SIZE_2D * 4 * sizeof(uint32_t), s_2DVertices, GL_DYNAMIC_DRAW);

			s_2DShader->Bind();
			
			s_2DShader->Mat4Arr("u_Model", (int)data.Objects2D.size(), &s_2DModel[0][0][0]);
			s_2DShader->V4Arr("u_Color", (int)data.Objects2D.size(), &s_2DColor[0][0]);
			
			s_2DShader->Tex2D("u_Texture", 0, s_DefTex);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_2DBuffers[EBO_2D_ID]);
			glDrawElements(GL_TRIANGLES, (int)(6 * data.Objects2D.size()), GL_UNSIGNED_INT, nullptr);
			
			Shader::UnBind();
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glBindVertexArray(0);
			
			data.Buffer->UnBind();
			s_Data.erase(s_Data.begin());
		}
	}
	
	void Renderer::Dispose()
	{
		glDeleteBuffers(2, s_2DBuffers);
		glDeleteVertexArrays(1, s_Arrays);
	}
}
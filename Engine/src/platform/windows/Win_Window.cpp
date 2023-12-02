#include "pch.h"
#include "Win_Window.h"
#include <stb/stb_image.h>

namespace overflow
{
	Win_Window::Win_Window(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Size = props.Size;

		CORE_INFO("Trying to create window {0} ({1}, {2})", props.Title, props.Size.x, props.Size.y);
		int glfwInitialized = glfwInit();
		CORE_ASSERT(glfwInitialized, "Unable to initialize GLFW")

		if(props.DebugOn) glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		else glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, props.Version.x);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, props.Version.y);
		glfwWindowHint(GLFW_OPENGL_PROFILE, (int)props.Profile);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

		GLFWmonitor* monitor = nullptr;
		switch (props.ScaleMode)
		{
			case WindowScaleMode::Windowed:
				glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
				glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
				break;
			case WindowScaleMode::Maximized:
				glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
				glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
				break;
			case WindowScaleMode::FullScreen:
				glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
				glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
				monitor = glfwGetPrimaryMonitor();
				vec2i pos = vec2i();
				glfwGetMonitorWorkarea(monitor, &pos.x, &pos.y,
				                       &m_Data.Size.x, &m_Data.Size.y);
				break;
		}

		m_Window = glfwCreateWindow(m_Data.Size.x, m_Data.Size.y,
									m_Data.Title.c_str(), monitor, nullptr);
		CORE_ASSERT(m_Window, "Unable to create window")

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(props.SyncMode);
		glfwGetWindowSize(m_Window, &m_Data.Size.x, &m_Data.Size.y);

		GLFWimage icons[2];
		unsigned char* imagePs[2];

		for (int i = 0; i < 2; ++i)
		{
			int width, height, numColCh;
			unsigned char* bytes = stbi_load(props.IconLocations[i].c_str(),
											 &width, &height, &numColCh, 0);
			imagePs[i] = bytes;
			icons[i] = GLFWimage(width, height, bytes);
		}

		glfwSetWindowIcon(m_Window, 2, icons);

		for (auto & imageP : imagePs) stbi_image_free(imageP);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Terminate();
			CORE_ASSERT(false, "Unable to initialize GLAD")
		}

		utils::EnableGLDebugging();
	}

	void Win_Window::SetVSync(VSyncMode mode)
	{
		glfwSwapInterval((int)mode);
		m_Data.SyncMode = mode;
	}

	void Win_Window::BeginDraw()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Win_Window::EndDraw()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	
	void Win_Window::Update()
	{
		Time::Update_Current(glfwGetTime());
	}
}
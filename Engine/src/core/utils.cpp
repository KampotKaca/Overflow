#include "pch.h"
#include "utils.h"

namespace overflow::utils
{
	void SetGLDebugLogLevel(DebugLogLevel level)
	{
		s_DebugLogLevel = level;
	}

	void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
	                      GLsizei length, const GLchar* message, const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:
				if ((int)s_DebugLogLevel > 0)
				{
					CORE_ASSERT(s_DebugLogLevel != DebugLogLevel::HighAssert,
								"[OpenGL] {0}: {1}", userParam, message)
				}
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				if ((int)s_DebugLogLevel > 2)
					CORE_WARN("[OpenGL] {0}: {1}", userParam, message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				if ((int)s_DebugLogLevel > 3)
					CORE_INFO("[OpenGL] {0}: {1}", userParam, message);
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				if ((int)s_DebugLogLevel > 4)
					CORE_TRACE("[OpenGL] {0}: {1}", userParam, message);
				break;
			default:
				CORE_ASSERT(false, "[OpenGL] {0}: {1}", userParam, message)
				break;
		}
	}

	void EnableGLDebugging()
	{
		glDebugMessageCallback(OpenGLLogMessage, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}

	bool i_case_compare(const std::string_view& str1, const std::string_view& str2)
	{
		return str1.size() == str2.size() &&
		       std::equal(str1.begin(), str1.end(), str2.begin(),
		                  [](char a, char b){
			                  return std::toupper(a) == std::toupper(b);
		                  });
	}

	std::_String_view_iterator<std::char_traits<char>> i_case_contains
			(const std::string_view& haystack, const std::string_view& needle)
	{
		return std::search(
				haystack.begin(), haystack.end(),
				needle.begin(), needle.end(),
				[](char a, char b)
				{ return std::toupper(a) == std::toupper(b); });
	}

	bool get_named_file(const std::filesystem::path& folder,
	                    const std::string& fileName, std::string& fName)
	{
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(folder))
		{
			if (is_regular_file(entry.status()) && entry.path().extension() != ".meta")
			{
				fName = entry.path().filename().string();
				if(((std::filesystem::path)fName).stem() == fileName) return true;
			}
		}

		return false;
	}
}
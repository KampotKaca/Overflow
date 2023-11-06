#include "pch.h"
#include "Shader.h"

namespace overflow
{
	static char NAME_BUFFER[64];

	static uint32_t CreateShader(GLenum shader, const std::string& source)
	{
		uint32_t sh = glCreateShader(shader);

		const char* str = source.c_str();
		glShaderSource(sh, 1, &str, nullptr);
		glCompileShader(sh);

		int success;
		glGetShaderiv(sh, GL_COMPILE_STATUS, &success);

		if(success != GL_TRUE)
		{
			int log_length = 0;
			glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &log_length);
			char* message = (char*) alloca(log_length * sizeof(char));
			glGetShaderInfoLog(sh, log_length, &log_length, message);

			glDeleteShader(sh);
			CORE_ASSERT(false, "[SHADER] creation failure with gl message: {0}", message)
			throw;
		}

		return sh;
	}

	Shader::Shader(UUID uuid, const std::string& vert, const std::string& frag)
		: Asset(uuid)
	{
		uint32_t vShader = CreateShader(GL_VERTEX_SHADER, vert),
				fShader = CreateShader(GL_FRAGMENT_SHADER, frag);

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vShader);
		glAttachShader(m_ID, fShader);
		glLinkProgram(m_ID);

		int link_status;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &link_status);

		if(link_status != GL_TRUE)
		{
			int log_length = 0;
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &log_length);
			char* message = (char*) alloca(log_length * sizeof(char));
			glGetProgramInfoLog(m_ID, log_length, &log_length, message);

			glDeleteProgram(m_ID);
			CORE_ASSERT(false, "[PROGRAM] link failure with gl message: {0}", message)
		}

		int numActiveUniforms;
		glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

		for (int i = 0; i < numActiveUniforms; ++i)
		{
			GLsizei bufSize = 64;
			GLsizei length;
			GLint size;
			GLenum type;
			std::string uniformName;

			glGetActiveUniform(m_ID, i, bufSize, &length, &size, &type, NAME_BUFFER);

			if(size > 1) continue;

			GLint blockIndex;
			uint32_t t = i;
			glGetActiveUniformsiv(m_ID, 1, &t, GL_UNIFORM_BLOCK_INDEX, &blockIndex);

			if(blockIndex == -1)
				m_UniformData.push_back({NAME_BUFFER, type, size });
		}

		glDetachShader(m_ID, vShader);
		glDetachShader(m_ID, fShader);
		glDeleteShader(vShader);
		glDeleteShader(fShader);
	}

	int Shader::NameToId(const char *loc)
	{
		auto l = m_Locations.find(loc);
		if(l == m_Locations.end())
		{
			int n = glGetUniformLocation(m_ID, loc);
			m_Locations[loc] = n;
			return n;
		}
		return l->second;
	}
}
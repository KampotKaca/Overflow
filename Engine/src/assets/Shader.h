#ifndef SHADER_H
#define SHADER_H

#include "Tex2D.h"
#include "core/utils.h"
#include "Asset.h"

namespace overflow
{
	struct UniformData
	{
		std::string Name;
		GLenum Type;
		int Size;
	};

	class Shader : public Asset
	{
	public:
		Shader() = default;
		Shader(UUID uuid, const std::string& vert, const std::string& frag);
		~Shader() override { glDeleteProgram(m_ID); }

		[[nodiscard]] uint32_t ShaderID()const { return m_ID; }
		void Bind()const { glUseProgram(m_ID); }
		static void UnBind() { glUseProgram(0); }
		int NameToId(const char *loc);

		//region Uniforms
		static void Float(int loc, float v)       { glUniform1f(loc, v); }
		static void Float(int loc, const vec2& v) { glUniform2f(loc, v.x, v.y); }
		static void Float(int loc, const vec3& v) { glUniform3f(loc, v.x, v.y, v.z); }
		static void Float(int loc, const vec4& v) { glUniform4f(loc, v.x, v.y, v.z, v.w); }

		void Float(const char* loc, float v)       { glUniform1f(NameToId(loc), v); }
		void Float(const char* loc, const vec2& v) { glUniform2f(NameToId(loc), v.x, v.y); }
		void Float(const char* loc, const vec3& v) { glUniform3f(NameToId(loc), v.x, v.y, v.z); }
		void Float(const char* loc, const vec4& v) { glUniform4f(NameToId(loc), v.x, v.y, v.z, v.w); }

		static void FArr(int loc, int count, const float* v)  { glUniform1fv(loc, count, v); }
		static void V2Arr(int loc, int count, const float* v) { glUniform2fv(loc, count, v); }
		static void V3Arr(int loc, int count, const float* v) { glUniform3fv(loc, count, v); }
		static void V4Arr(int loc, int count, const float* v) { glUniform4fv(loc, count, v); }

		void FArr(const char* loc, int count, const float* v)  { glUniform1fv(NameToId(loc), count, v); }
		void V2Arr(const char* loc, int count, const float* v) { glUniform2fv(NameToId(loc), count, v); }
		void V3Arr(const char* loc, int count, const float* v) { glUniform3fv(NameToId(loc), count, v); }
		void V4Arr(const char* loc, int count, const float* v) { glUniform4fv(NameToId(loc), count, v); }

		static void Mat2(int loc, const float* f)   { glUniformMatrix2fv(loc, 1, false, f); }
		static void Mat3(int loc, const float* f)   { glUniformMatrix3fv(loc, 1, false, f); }
		static void Mat4(int loc, const float* f)   { glUniformMatrix4fv(loc, 1, false, f); }

		void Mat2(const char* loc, const float* f) { glUniformMatrix2fv(NameToId(loc), 1, false, f); }
		void Mat3(const char* loc, const float* f) { glUniformMatrix3fv(NameToId(loc), 1, false, f); }
		void Mat4(const char* loc, const float* f) { glUniformMatrix4fv(NameToId(loc), 1, false, f); }

		static void Mat2Arr(int loc, int count, const float* f) { glUniformMatrix2fv(loc, count, false, f); }
		static void Mat3Arr(int loc, int count, const float* f) { glUniformMatrix3fv(loc, count, false, f); }
		static void Mat4Arr(int loc, int count, const float* f) { glUniformMatrix4fv(loc, count, false, f); }

		void Mat2Arr(const char* loc, int count, const float* f) { glUniformMatrix2fv(NameToId(loc), count, false, f); }
		void Mat3Arr(const char* loc, int count, const float* f) { glUniformMatrix3fv(NameToId(loc), count, false, f); }
		void Mat4Arr(const char* loc, int count, const float* f) { glUniformMatrix4fv(NameToId(loc), count, false, f); }

		static void Tex2D(int loc, int texUnit, const Tex2D* tex)
		{
			tex->Bind(texUnit);
			glUniform1i(loc, texUnit);
		}

		void Tex2D(const char* loc, int texUnit, const class Tex2D* tex)
		{
			tex->Bind(texUnit);
			glUniform1i(NameToId(loc), texUnit);
		}
		
		static void Tex2D(int loc, int texUnit, uint32_t texId)
		{
			glActiveTexture(texUnit + GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texId);
			glUniform1i(loc, texUnit);
		}
		
		void Tex2D(const char* loc, int texUnit, uint32_t texId)
		{
			glActiveTexture(texUnit + GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texId);
			glUniform1i(NameToId(loc), texUnit);
		}
		//endregion

	private:
		uint32_t m_ID = 0;
		std::unordered_map<std::string, int32_t> m_Locations;
		std::vector<UniformData> m_UniformData;

		friend class Material;
	};
}

#endif //SHADER_H

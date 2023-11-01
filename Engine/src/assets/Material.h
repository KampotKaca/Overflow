#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "Tex2D.h"

namespace overflow
{
	class Material
	{
	public:
		Material() = default;
		Material(UUID uuid, Shader* shader);
		~Material() = default;

		//region Uniforms
		void SetFloat(const char* key, float v);
		void SetFloat(const char* key, const vec2& v);
		void SetFloat(const char* key, const vec3& v);
		void SetFloat(const char* key, const vec4& v);
		void SetTex  (const char* key, Tex2D* v);
		//endregion

		[[nodiscard]] bool IsValid() const { return m_Shader != nullptr; }
		[[nodiscard]] Shader* GetShader() const { return m_Shader; }
		void SetShader(Shader* shader);

	private:
		UUID m_UUID;
		Shader* m_Shader = nullptr;
		std::unordered_map<int, float> m_Floats;
		std::unordered_map<int, vec2> m_Vec2s;
		std::unordered_map<int, vec3> m_Vec3s;
		std::unordered_map<int, vec4> m_Vec4s;
		std::unordered_map<int, Tex2D*> m_Tex2Ds;
	};
}

#endif //MATERIAL_H

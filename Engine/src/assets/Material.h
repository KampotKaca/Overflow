#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "Tex2D.h"
#include "Asset.h"

namespace overflow
{
	class Material : public Asset
	{
	public:
		Material() = default;
		Material(UUID uuid, ref<Shader> shader);
		~Material() override = default;

		//region Uniforms
		void SetFloat(const char* key, float v);
		void SetFloat(const char* key, const vec2& v);
		void SetFloat(const char* key, const vec3& v);
		void SetFloat(const char* key, const vec4& v);
		void SetTex  (const char* key, ref<Tex2D> v);
		//endregion

		[[nodiscard]] bool IsValid() const { return m_Shader != nullptr; }
		[[nodiscard]] ref<Shader> GetShader() const { return m_Shader; }
		void SetShader(const ref<Shader>& shader);

	private:
		ref<Shader> m_Shader = nullptr;
		std::unordered_map<int, float> m_Floats;
		std::unordered_map<int, vec2> m_Vec2s;
		std::unordered_map<int, vec3> m_Vec3s;
		std::unordered_map<int, vec4> m_Vec4s;
		std::unordered_map<int, ref<Tex2D>> m_Tex2Ds;
	};
}

#endif //MATERIAL_H

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Asset.h"
#include "Shader.h"
#include "Tex2D.h"

namespace overflow
{
	class Material : public Asset
	{
	public:
		Material(UUID uuid);
		~Material() override = default;

		//region Uniforms
		void SetFloat(const char* key, float v)             { m_Floats[key] = v; }
		void SetFloat(const char* key, const vec2& v)       { m_Vec2s[key] = v; }
		void SetFloat(const char* key, const vec3& v)       { m_Vec3s[key] = v; }
		void SetFloat(const char* key, const vec4& v)       { m_Vec4s[key] = v; }
		void SetTex  (const char* key, const ref<Tex2D>& v) { m_Tex2Ds[key] = v; }
		//endregion

		[[nodiscard]] bool IsValid() const { return m_Shader != nullptr; }
		[[nodiscard]] ref<Shader> GetShader() const { return m_Shader; }

		template<typename T>
		struct MaterialData
		{
			std::string id;
			T data;
		};

	private:
		ref<Shader> m_Shader = nullptr;
		std::unordered_map<std::string, float> m_Floats;
		std::unordered_map<std::string, vec2> m_Vec2s;
		std::unordered_map<std::string, vec3> m_Vec3s;
		std::unordered_map<std::string, vec4> m_Vec4s;
		std::unordered_map<std::string, ref<Tex2D>> m_Tex2Ds;

		void OnReload() override {}
		void Postload(UUID shader,
					  std::vector<MaterialData<float>>& floats,
					  std::vector<MaterialData<vec2>>& vec2s,
					  std::vector<MaterialData<vec3>>& vec3s,
					  std::vector<MaterialData<vec4>>& vec4s,
					  std::vector<MaterialData<UUID>>& textures);
	};
}

#endif //MATERIAL_H

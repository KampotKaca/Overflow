#include "pch.h"
#include "Material.h"

namespace overflow
{
	Material::Material(UUID uuid) : Asset(uuid)
	{

	}

	void Material::Postload(UUID shader,
	                        std::vector<MaterialData<float>>& floats,
					        std::vector<MaterialData<vec2>>& vec2s,
					        std::vector<MaterialData<vec3>>& vec3s,
					        std::vector<MaterialData<vec4>>& vec4s,
					        std::vector<MaterialData<UUID>>& textures)
	{
		m_Shader = AssetPipeline::GetAsset<Shader>(shader);
		if(m_Shader == nullptr) return;

		for (auto& var : floats) m_Floats[var.id] = var.data;
		for (auto& var : vec2s) m_Vec2s[var.id] = var.data;
		for (auto& var : vec3s) m_Vec3s[var.id] = var.data;
		for (auto& var : vec4s) m_Vec4s[var.id] = var.data;

		for (auto& var : textures)
			m_Tex2Ds[var.id] = AssetPipeline::GetAsset<Tex2D>(var.data);
	}
}
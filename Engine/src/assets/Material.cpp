#include "pch.h"
#include "Material.h"

namespace overflow
{
	Material::Material(UUID uuid, Shader* shader)
	: m_UUID(uuid)
	{
		SetShader(shader);
	}

	void Material::SetShader(Shader *shader)
	{
		if(shader == m_Shader) return;

		m_Floats.clear();
		m_Vec2s .clear();
		m_Vec3s .clear();
		m_Vec4s .clear();
		m_Tex2Ds.clear();

		if(shader == nullptr)
		{
			m_Shader = nullptr;
			return;
		}

		m_Shader = shader;

		for(auto& uniform : m_Shader->m_UniformData)
		{
			auto id = m_Shader->NameToId(uniform.Name.c_str());
			switch (uniform.Type)
			{
				case GL_FLOAT:      m_Floats[id] = 0;        break;
				case GL_FLOAT_VEC2: m_Vec2s [id] = vec2();   break;
				case GL_FLOAT_VEC3: m_Vec3s [id] = vec3();   break;
				case GL_FLOAT_VEC4: m_Vec4s [id] = vec4();   break;
				case GL_SAMPLER_2D: m_Tex2Ds[id] = nullptr;  break;
			}
		}
	}

	//region Uniforms
	void Material::SetFloat(const char *key, float v)
	{
		if(m_Shader == nullptr)
		{
			CORE_ERROR("[MATERIAL] cannot set uniform when shader is not specified!!!");
			return;
		}

		auto it = m_Floats.find(m_Shader->NameToId(key));
		if(it == m_Floats.end())
		{
			CORE_ERROR("[MATERIAL] invalid uniform name or type");
			return;
		}
		it->second = v;
	}

	void Material::SetFloat(const char *key, const vec2 &v)
	{
		if(m_Shader == nullptr)
		{
			CORE_ERROR("[MATERIAL] cannot set uniform when shader is not specified!!!");
			return;
		}

		auto it = m_Vec2s.find(m_Shader->NameToId(key));
		if(it == m_Vec2s.end())
		{
			CORE_ERROR("[MATERIAL] invalid uniform name or type");
			return;
		}
		it->second = v;
	}

	void Material::SetFloat(const char *key, const vec3 &v)
	{
		if(m_Shader == nullptr)
		{
			CORE_ERROR("[MATERIAL] cannot set uniform when shader is not specified!!!");
			return;
		}

		auto it = m_Vec3s.find(m_Shader->NameToId(key));
		if(it == m_Vec3s.end())
		{
			CORE_ERROR("[MATERIAL] invalid uniform name or type");
			return;
		}
		it->second = v;
	}

	void Material::SetFloat(const char *key, const vec4 &v)
	{
		if(m_Shader == nullptr)
		{
			CORE_ERROR("[MATERIAL] cannot set uniform when shader is not specified!!!");
			return;
		}

		auto it = m_Vec4s.find(m_Shader->NameToId(key));
		if(it == m_Vec4s.end())
		{
			CORE_ERROR("[MATERIAL] invalid uniform name or type");
			return;
		}
		it->second = v;
	}

	void Material::SetTex(const char *key, Tex2D* v)
	{
		if(m_Shader == nullptr)
		{
			CORE_ERROR("[MATERIAL] cannot set uniform when shader is not specified!!!");
			return;
		}

		auto it = m_Tex2Ds.find(m_Shader->NameToId(key));
		if(it == m_Tex2Ds.end())
		{
			CORE_ERROR("[MATERIAL] invalid uniform name or type");
			return;
		}
		it->second = v;
	}
	//endregion
}
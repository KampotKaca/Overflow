#include "pch.h"
#include "AssetUtility.h"
#include "overflow.h"

namespace overflow::edit::utils
{
	const std::unordered_map<std::string, AssetType> s_Types =
	{
		{ "Shader",   AssetType::Shader },
		{ "Tex2D",    AssetType::Tex2D },
		{ "Mesh",     AssetType::Mesh },
		{ "Material", AssetType::Material },
		{ "Scene",    AssetType::Scene }
	};

	void* LoadAsset(const std::filesystem::path &root, const std::filesystem::path &location, bool reload)
	{
		if(!std::filesystem::exists(location))
		{
			CORE_ASSERT(false, "Invalid Asset Path {0}", location)
			return nullptr;
		}

		Deserializer doc(location);
		uint64_t uuid;
		doc.GetUInt64("__uuid", uuid, UUID());
		void* existent = AssetPipeline::Find((UUID)uuid);

		if(!(existent == nullptr || reload)) return existent;

		std::string tString;
		if(!doc.GetString("__type", tString))
		{
			CORE_ERROR("Invalid Asset Type!!!");
			return nullptr;
		}

		auto it = s_Types.find(tString);
		if(it == s_Types.end())
		{
			CORE_ERROR("Invalid Asset Type!!!");
			return nullptr;
		}

		AssetType type = it->second;
		switch (type)
		{
			case AssetType::Shader:     return LoadShader(root, doc, (UUID)uuid);
			case AssetType::Tex2D:      return LoadTex2D(root, doc, (UUID)uuid);
			case AssetType::Mesh:       return LoadMesh(root, doc, (UUID)uuid);
			case AssetType::Material:   return LoadMaterial(root, doc, (UUID)uuid);
			case AssetType::Scene:      return LoadScene(root, doc, (UUID)uuid);
		}
	}

	void* LoadShader(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
	{
		std::string tempStr;
		std::filesystem::path vPath;

		if(!doc.GetString("vPath", tempStr))
		{
			CORE_ASSERT(false, "Shader doesn't include vertex path")
			return nullptr;
		}

		vPath = (root / tempStr).generic_string();
		std::filesystem::path fPath;

		if(!doc.GetString("fPath", tempStr))
		{
			CORE_ASSERT(false, "Shader doesn't include fragment path")
			return nullptr;
		}

		fPath = (root / tempStr).generic_string();

		if(!std::filesystem::exists(vPath))
		{
			CORE_ASSERT(false, "[SHADER] location {0} doesn't exist", vPath)
			return nullptr;
		}

		if(!std::filesystem::exists(fPath))
		{
			CORE_ASSERT(false, "[SHADER] location {0} doesn't exist", fPath)
			return nullptr;
		}

		std::string vSource, fSource;

		std::ifstream vStream = std::ifstream(vPath);
		std::ifstream fStream = std::ifstream(fPath);

		std::string line;
		while (std::getline(vStream, line))
		{
			vSource.append(line).append("\n");
		}

		while (std::getline(fStream, line))
		{
			fSource.append(line).append("\n");
		}

		vStream.close();
		fStream.close();

		return AssetPipeline::CreateShader(uuid, vSource, fSource, true);
	}

	void* LoadTex2D(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
	{
		std::string tempStr;
		if(!doc.GetString("texPath", tempStr))
		{
			CORE_ASSERT(false, "Tex2D doesn't include tex2D path")
			return nullptr;
		}

		std::filesystem::path texPath = (root / tempStr).generic_string();

		if(!std::filesystem::exists(texPath))
		{
			CORE_ASSERT(false, "[TEX2D] location {0} doesn't exist", texPath)
			return nullptr;
		}

		int width, height, numChannels;
		byte* data = stbi_load(texPath.string().c_str(), &width, &height, &numChannels, 0);

		int filter, wrap;
		bool mipmaps;
		doc.GetInt32("filter", filter, GL_NEAREST);
		doc.GetInt32("wrap", wrap, GL_REPEAT);
		doc.GetBool("mipmaps", mipmaps, true);

		return AssetPipeline::CreateTex2D(uuid, data, vec2i{ width, height },
			numChannels, filter, wrap, mipmaps, true);
	}

	void* LoadMesh(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
	{
		std::string tempStr;
		if(!doc.GetString("meshPath", tempStr))
		{
			CORE_ASSERT(false, "Mesh doesn't include mesh path")
			return nullptr;
		}

		std::filesystem::path meshPath = (root / tempStr).generic_string();

		if(!std::filesystem::exists(meshPath))
		{
			CORE_ASSERT(false, "[MESH] location {0} doesn't exist", meshPath)
			return nullptr;
		}

		return nullptr;
	}

#define MATERIAL_MAP(v_type, v_name, matFuncName, funcName) \
	if(doc.PushArray(v_name))\
	{\
		for (size_t i = 0; i < doc.size(); i++)\
		{\
			doc.SetByIndex(i);\
			std::string name;\
			if(!doc.GetString("name", name)) continue;\
			v_type v;\
			if(!doc.funcName("var", v)) continue;\
			matFuncName(name.c_str(), v);\
		}\
		doc.PopArray();\
	}

	void* LoadMaterial(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
	{
		uint64_t shaderId;
		if(!doc.GetUInt64("shader", shaderId))
		{
			CORE_ASSERT(false, "Material doesn't include shader uuid")
			return nullptr;
		}

		auto* shader = AssetPipeline::GetShader((UUID)shaderId);
		auto* mat = AssetPipeline::CreateMaterial(uuid, shader, true);

		MATERIAL_MAP(float, "Floats", mat->SetFloat, GetFloat)
		MATERIAL_MAP(vec2,  "Vec2s",  mat->SetFloat, GetVec2)
		MATERIAL_MAP(vec3,  "Vec3s",  mat->SetFloat, GetVec3)
		MATERIAL_MAP(vec4,  "Vec4s",  mat->SetFloat, GetVec4)

		if (doc.PushArray("Vec4s"))
		{
			for (size_t i = 0; i < doc.size(); i++) {
				doc.SetByIndex(i);
				std::string name;
				if (!doc.GetString("name", name))continue;
				uint64_t v;
				if (!doc.GetUInt64("var", v))continue;

				auto* tex = AssetPipeline::GetTex2D((UUID)v);
				if(tex != nullptr) mat->SetTex(name.c_str(), tex);
			}
			doc.PopArray();
		}

		return mat;
	}

#undef MATERIAL_MAP

	void* LoadScene(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
	{
		return nullptr;
	}
}
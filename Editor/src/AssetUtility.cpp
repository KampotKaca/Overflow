#include "pch.h"
#include "AssetUtility.h"
#include "overflow.h"

namespace overflow::edit::utils
{
	static std::unordered_map<uint64_t, EditorAsset> s_Assets;
	const std::unordered_map<std::string, AssetType> s_Types =
	{
		{ ".sha",   AssetType::Shader },
		{ ".tex",   AssetType::Tex2D },
		{ ".mesh",  AssetType::Mesh },
		{ ".mat",   AssetType::Material },
	};

	const std::unordered_map<std::string, AssetType> s_Formats =
	{
		{ ".png", AssetType::Tex2D },
		{ ".jpg", AssetType::Tex2D },
		{ ".obj", AssetType::Mesh },
		{ ".fbx", AssetType::Mesh },
	};

	void LoadEditorAssets()
	{
		TryCreateTemporaries(RES_PATH, RES_PATH);

		LoadAssetsByExtension(RES_PATH, RES_PATH, ".sha");
		LoadAssetsByExtension(RES_PATH, RES_PATH, ".tex");
		LoadAssetsByExtension(RES_PATH, RES_PATH, ".mat");
	}

	void TryCreateTemporaries(const std::filesystem::path &root, const std::filesystem::path &loc, const std::filesystem::path &lPath)
	{
		std::vector<std::filesystem::path> validFiles;
		std::vector<std::filesystem::path> folders;

		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(loc))
		{
			if (is_directory(entry.status())) folders.push_back(entry.path());
			else if (is_regular_file(entry.status()) && s_Formats.find(entry.path().extension().string()) != s_Formats.end())
				validFiles.push_back((std::filesystem::path)entry.path().generic_string());
		}

		while (!validFiles.empty())
		{
			std::string ext = validFiles.begin()->extension().string();
			auto it = s_Formats.find(ext);
			switch (it->second)
			{
				default: break;
				case AssetType::Tex2D: CreateTex2DAsset(*validFiles.begin(), lPath); break;
				case AssetType::Mesh: CreateMeshAsset(*validFiles.begin(), lPath); break;
			}

			validFiles.erase(validFiles.begin());
		}

		for (auto& entry : folders)
		{
			std::filesystem::path newLPath = lPath;
			newLPath /= entry.filename();
			TryCreateTemporaries(root, entry, newLPath.generic_string());
		}
	}

	void CreateTex2DAsset(const std::filesystem::path &loc, const std::filesystem::path &lPath)
	{
		std::filesystem::path newPath = loc.parent_path();
		newPath /= loc.stem();
		newPath += ".tex";
		newPath = newPath.generic_string();
		if(!std::filesystem::exists(newPath))
		{
			Serializer doc(newPath);
			doc.Push("__uuid", UUID());

			std::filesystem::path localPath = lPath.generic_string();
			localPath /= loc.filename().string();

			doc.Push("texPath", localPath.string());
			doc.Push("filter", GL_NEAREST);
			doc.Push("wrap", GL_REPEAT);
			doc.Push("mipmaps", true);

			doc.Save();
		}
	}

	void CreateMeshAsset(const std::filesystem::path &loc, const std::filesystem::path &lPath)
	{
		std::filesystem::path newPath = loc.stem();
		newPath += ".mesh";

		Serializer doc(newPath);
		doc.Push("__uuid", UUID());

		std::string localPath = lPath.generic_string();
		localPath += loc.filename().string();

		doc.Push("meshPath", localPath);

		doc.Save();
	}

	void LoadAssetsByExtension(const std::filesystem::path &root, const std::filesystem::path &loc, const std::string& ext)
	{
		for (const auto& entry : std::filesystem::directory_iterator(loc))
		{
			if(std::filesystem::is_directory(entry))
			{
				LoadAssetsByExtension(root, entry.path(), ext);
				continue;
			}

			if (entry.path().extension() == ext) LoadAsset(root, entry.path());
		}
	}

	ref<Asset> LoadAsset(const std::filesystem::path &root, const std::filesystem::path &location, bool reload)
	{
		if(!std::filesystem::exists(location))
		{
			CORE_ASSERT(false, "Invalid Asset Path {0}", location)
			return nullptr;
		}

		auto it = s_Types.find(location.extension().string());
		if(it == s_Types.end())
		{
			CORE_ERROR("Invalid Asset Type!!!");
			return nullptr;
		}

		Deserializer doc(location);
		uint64_t uuid;
		doc.GetUInt64("__uuid", uuid, UUID());
		ref<Asset> existent = AssetPipeline::Find((UUID)uuid);

		if(!(existent == nullptr || reload)) return existent;

		AssetType type = it->second;
		ref<Asset> asset;
		switch (type)
		{
			case AssetType::Shader:     asset = LoadShader(root, doc, (UUID)uuid);   break;
			case AssetType::Tex2D:      asset = LoadTex2D(root, doc, (UUID)uuid);    break;
			case AssetType::Mesh:       asset = LoadMesh(root, doc, (UUID)uuid);     break;
			case AssetType::Material:   asset = LoadMaterial(root, doc, (UUID)uuid); break;
		}

		s_Assets[asset->GetUUID()] = EditorAsset{ asset, type, location.filename().stem().string(), "", location };
		return asset;
	}
	
	ref<Asset> LoadShader(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
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

		return AssetPipeline::Create<Shader>(uuid, vSource, fSource);
	}
	
	ref<Asset> LoadTex2D(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
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

		int width = 0, height = 0, numChannels = 0;
		stbi_set_flip_vertically_on_load(1);
		byte* data = stbi_load(texPath.string().c_str(), &width, &height, &numChannels, 0);

		if(!data)
		{
			CORE_ERROR("Could not load the image {0}, reason: {1}", texPath, stbi_failure_reason());
			return nullptr;
		}

		int filter, wrap;
		bool mipmaps;
		doc.GetInt32("filter", filter, GL_NEAREST);
		doc.GetInt32("wrap", wrap, GL_REPEAT);
		doc.GetBool("mipmaps", mipmaps, true);

		auto tex = AssetPipeline::Create<Tex2D>(uuid, data, vec2i{ width, height },
			numChannels, filter, wrap, mipmaps);

		stbi_image_free(data);

		return tex;
	}
	
	ref<Asset> LoadMesh(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
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
	
	ref<Asset> LoadMaterial(const std::filesystem::path &root, Deserializer& doc, UUID uuid)
	{
		uint64_t shaderId;
		if(!doc.GetUInt64("shader", shaderId))
		{
			CORE_ASSERT(false, "Material doesn't include shader uuid")
			return nullptr;
		}

		auto shader = AssetPipeline::GetAsset<Shader>((UUID)shaderId);
		auto mat = AssetPipeline::Create<Material>(uuid, shader);

		MATERIAL_MAP(float, "floats", mat->SetFloat, GetFloat)
		MATERIAL_MAP(vec2,  "vec2s",  mat->SetFloat, GetVec2)
		MATERIAL_MAP(vec3,  "vec3s",  mat->SetFloat, GetVec3)
		MATERIAL_MAP(vec4,  "vec4s",  mat->SetFloat, GetVec4)

		if (doc.PushArray("tex2Ds"))
		{
			for (size_t i = 0; i < doc.size(); i++) {
				doc.SetByIndex(i);
				std::string name;
				if (!doc.GetString("name", name))continue;
				uint64_t v;
				if (!doc.GetUInt64("var", v))continue;

				auto tex = AssetPipeline::GetAsset<Tex2D>((UUID)v);
				if(tex != nullptr) mat->SetTex(name.c_str(), tex);
			}
			doc.PopArray();
		}

		return mat;
	}

#undef MATERIAL_MAP

	void* LoadScene(const std::filesystem::path &location)
	{
		return nullptr;
	}

	EditorAsset GetAsset(UUID uuid) { return s_Assets[uuid]; }

	void FindAssets(AssetType type, std::vector<EditorAsset>& assets)
	{
		for (auto& item : s_Assets)
			if(item.second.Type == type) assets.push_back(item.second);
	}
}
#include "pch.h"
#include "AssetPipeline.h"

namespace overflow
{
	std::unordered_map<uint64_t, Shader> AssetPipeline::s_Shaders;
	std::unordered_map<uint64_t, Tex2D> AssetPipeline::s_Tex2Ds;
	std::unordered_map<uint64_t, Mesh> AssetPipeline::s_Meshes;
	std::unordered_map<uint64_t, Material> AssetPipeline::s_Materials;

	Asset* AssetPipeline::Find(UUID uuid)
	{
		Asset* val;
		val = GetShader(uuid);
		if(val != nullptr) return val;
		val = GetTex2D(uuid);
		if(val != nullptr) return val;
		val = GetMesh(uuid);
		if(val != nullptr) return val;
		val = GetMaterial(uuid);
		return val;
	}

	bool AssetPipeline::Exists(UUID uuid)
	{
		if(ShaderExists(uuid))   return true;
		if(Tex2DExists(uuid))    return true;
		if(MeshExists(uuid))     return true;
		if(MaterialExists(uuid)) return true;
		return false;
	}

#define CREATION(type, collection, uuid, reload, ...) \
	auto it = collection.find(uuid);\
	if(it == collection.end())\
	{\
		collection[uuid] = type(uuid, __VA_ARGS__);\
		it = collection.find(uuid);\
	}\
	else if(reload) it->second = type(uuid, __VA_ARGS__);\
    else return nullptr;\
	return &it->second;

	Shader *AssetPipeline::GetShader(UUID uuid)
	{
		auto it = s_Shaders.find(uuid);
		if(it == s_Shaders.end()) return nullptr;

		return &it->second;
	}

	bool AssetPipeline::ShaderExists(UUID uuid)
	{
		auto it = s_Shaders.find(uuid);
		return it != s_Shaders.end();
	}

	Shader *AssetPipeline::CreateShader(UUID uuid, const std::string &vert,
										const std::string &frag, bool reload)
	{ CREATION(Shader, s_Shaders, uuid, reload, vert, frag) }

	Tex2D *AssetPipeline::GetTex2D(UUID uuid)
	{
		auto it = s_Tex2Ds.find(uuid);
		if(it == s_Tex2Ds.end()) return nullptr;

		return &it->second;
	}

	bool AssetPipeline::Tex2DExists(UUID uuid)
	{
		auto it = s_Tex2Ds.find(uuid);
		return it != s_Tex2Ds.end();
	}

	Tex2D* AssetPipeline::CreateTex2D(UUID uuid, byte *data, vec2i size, int numColCh,
	                                  int filter, int wrap, bool mipmaps, bool reload)
	{
		CREATION(Tex2D, s_Tex2Ds, uuid, reload,
		         data, size, numColCh, filter, wrap, mipmaps)
	}

	Mesh *AssetPipeline::GetMesh(UUID uuid)
	{
		auto it = s_Meshes.find(uuid);
		if(it == s_Meshes.end()) return nullptr;

		return &it->second;
	}

	bool AssetPipeline::MeshExists(UUID uuid)
	{
		auto it = s_Meshes.find(uuid);
		return it != s_Meshes.end();
	}

	Mesh *AssetPipeline::CreateMesh(UUID uuid, std::vector<Vertex> &&vertices,
	                                std::vector<uint32_t> &&indices, bool reload)
	{
		CREATION(Mesh, s_Meshes, uuid, reload, std::move(vertices), std::move(indices))
	}

	Material *AssetPipeline::GetMaterial(UUID uuid)
	{
		auto it = s_Materials.find(uuid);
		if(it == s_Materials.end()) return nullptr;

		return &it->second;
	}

	bool AssetPipeline::MaterialExists(UUID uuid)
	{
		auto it = s_Materials.find(uuid);
		return it != s_Materials.end();
	}

	Material *AssetPipeline::CreateMaterial(UUID uuid, Shader* shader, bool reload)
	{ CREATION(Material, s_Materials, uuid, reload, shader) }

#undef CREATION
}
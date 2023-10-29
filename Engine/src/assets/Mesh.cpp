#include "pch.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace overflow
{
	
	ref<Mesh> Mesh::Import(const std::filesystem::path& location)
	{
		Assimp::Importer importer;
		
		uint32_t flags = aiProcess_Triangulate | aiProcess_FlipUVs;
		const aiScene* scene = importer.ReadFile(location.generic_string(), flags);
	}
	
	void Mesh::OnReload()
	{
	
	}
}
#ifndef ASSET_PIPELINE_H
#define ASSET_PIPELINE_H

#include "core/utils.h"
#include "Shader.h"
#include "Tex2D.h"
#include "Mesh.h"
#include "Material.h"

namespace overflow
{
	class AssetPipeline
	{
	public:
		static Asset* Find(UUID uuid);
		static bool Exists(UUID uuid);

		static Shader* GetShader(UUID uuid);
		static bool ShaderExists(UUID uuid);
		static Shader* CreateShader(UUID uuid, const std::string& vert, const std::string& frag, bool reload = false);

		static Tex2D* GetTex2D(UUID uuid);
		static bool Tex2DExists(UUID uuid);
		static Tex2D* CreateTex2D(UUID uuid, byte* data, vec2i size,
		                          int numColCh, int filter = GL_LINEAR,
		                          int wrap = GL_REPEAT, bool mipmaps = true, bool reload = false);

		static Mesh* GetMesh(UUID uuid);
		static bool MeshExists(UUID uuid);
		static Mesh* CreateMesh(UUID uuid, std::vector<Vertex>&& vertices,
		                        std::vector<uint32_t>&& indices, bool reload = false);

		static Material* GetMaterial(UUID uuid);
		static bool MaterialExists(UUID uuid);
		static Material* CreateMaterial(UUID uuid, Shader* shader, bool reload = false);

	private:
		static std::unordered_map<uint64_t, Shader> s_Shaders;
		static std::unordered_map<uint64_t, Tex2D> s_Tex2Ds;
		static std::unordered_map<uint64_t, Mesh> s_Meshes;
		static std::unordered_map<uint64_t, Material> s_Materials;
	};
}

#endif //ASSET_PIPELINE_H

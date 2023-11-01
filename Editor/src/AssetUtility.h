#ifndef ASSET_UTILITY_H
#define ASSET_UTILITY_H

#include "core/serialization/Serializer.h"
#include "core/serialization/Deserializer.h"

namespace overflow::edit::utils
{
	void LoadEditorAssets();
	void LoadAssetsByExtension(const std::filesystem::path &root, const std::filesystem::path &loc, const std::string& ext);
	void* LoadAsset(const std::filesystem::path &root, const std::filesystem::path &location, bool reload = false);
	void* LoadShader(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	void* LoadTex2D(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	void* LoadMesh(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	void* LoadMaterial(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	void* LoadScene(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
}

#endif //ASSET_UTILITY_H

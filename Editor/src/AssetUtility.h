#ifndef ASSET_UTILITY_H
#define ASSET_UTILITY_H

#include "assets/Asset.h"
#include "core/serialization/Serializer.h"
#include "core/serialization/Deserializer.h"

namespace overflow::edit::utils
{
	void LoadEditorAssets();
	void LoadAssetsByExtension(const std::filesystem::path &root, const std::filesystem::path &loc, const std::string& ext);
	Asset* LoadAsset(const std::filesystem::path &root, const std::filesystem::path &location, bool reload = false);
	Asset* LoadShader(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	Asset* LoadTex2D(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	Asset* LoadMesh(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	Asset* LoadMaterial(const std::filesystem::path &root, Deserializer& doc, UUID uuid);

	void* LoadScene(const std::filesystem::path &location);
	struct EditorAsset
	{
		Asset* Asset;
		AssetType Type;
		std::string Name;
		std::string LocationCompat;
		std::filesystem::path FullLocation;
	};

	EditorAsset GetAsset(UUID uuid);
	void FindAssets(AssetType type, std::vector<EditorAsset>& assets);
}

#endif //ASSET_UTILITY_H

#ifndef ASSET_UTILITY_H
#define ASSET_UTILITY_H

#include "assets/Asset.h"
#include "core/serialization/Serializer.h"
#include "core/serialization/Deserializer.h"

namespace overflow::edit::utils
{
	void LoadEditorAssets();
	void TryCreateTemporaries(const std::filesystem::path &root, const std::filesystem::path &loc, const std::filesystem::path &lPath = "");
	void LoadAssetsByExtension(const std::filesystem::path &root, const std::filesystem::path &loc, const std::string& ext, bool isEditorAsset = false);

	void CreateTex2DAsset(const std::filesystem::path &loc, const std::filesystem::path &lPath);
	void CreateMeshAsset(const std::filesystem::path &loc, const std::filesystem::path &lPath);

	ref<Asset> LoadAsset(const std::filesystem::path &root, const std::filesystem::path &location, bool isEditorAsset = false);
	ref<Asset> LoadShader(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	ref<Asset> LoadTex2D(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	ref<Asset> LoadMesh(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	ref<Asset> LoadMaterial(const std::filesystem::path &root, Deserializer& doc, UUID uuid);

	void* LoadScene(const std::filesystem::path &location);
	struct EditorAsset
	{
		ref<Asset> Asset;
		AssetType Type;
		std::string Name;
		std::string LocationCompat;
		std::filesystem::path FullLocation;
	};

	EditorAsset GetAsset(UUID uuid);
	void FindAssets(AssetType type, std::vector<EditorAsset>& assets);
}

#endif //ASSET_UTILITY_H

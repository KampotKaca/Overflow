#ifndef ASSET_UTILITY_H
#define ASSET_UTILITY_H

#include "core/serialization/Serializer.h"
#include "core/serialization/Deserializer.h"

namespace overflow::edit::utils
{
	static void* LoadAsset(const std::filesystem::path &root, const std::filesystem::path &location, bool reload = false);
	static void* LoadShader(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	static void* LoadTex2D(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	static void* LoadMesh(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	static void* LoadMaterial(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
	static void* LoadScene(const std::filesystem::path &root, Deserializer& doc, UUID uuid);
}

#endif //ASSET_UTILITY_H

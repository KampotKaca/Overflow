#include "pch.h"
#include "AssetPipeline.h"

namespace overflow
{
	std::unordered_map<uint64_t, ref<Asset>> AssetPipeline::s_Assets;

	ref<Asset> AssetPipeline::Find(UUID uuid)
	{
		auto it = s_Assets.find(uuid);
		if(it == s_Assets.end()) return nullptr;
		
		return it->second;
	}
	
	bool AssetPipeline::Exists(UUID uuid)
	{
		return s_Assets.find(uuid) != s_Assets.end();
	}

#undef CREATION
}
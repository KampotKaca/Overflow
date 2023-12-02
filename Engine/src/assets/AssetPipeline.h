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
		static ref<Asset> Find(UUID uuid);
		static bool Exists(UUID uuid);
		
		template <typename T>
		static ref<T> GetAsset(UUID uuid)
		{
			auto it = s_Assets.find(uuid);
			if(it == s_Assets.end()) return nullptr;
			
			return over_cast(T, it->second);
		}
		
		template<typename T, typename... Args>
		static ref<T> Create(UUID uuid, Args&&... args)
		{
			auto it = s_Assets.find(uuid);
			if (it == s_Assets.end())
			{
				s_Assets[uuid] = make_ref(T, uuid, std::forward<Args>(args)...);
				it = s_Assets.find(uuid);
			}
			else return nullptr;
			return over_cast(T, it->second);
		}

	private:
		static std::unordered_map<uint64_t, ref<Asset>> s_Assets;
	};
}

#endif //ASSET_PIPELINE_H

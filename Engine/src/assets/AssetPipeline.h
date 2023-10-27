#ifndef ASSET_PIPELINE_H
#define ASSET_PIPELINE_H

#include "core/utils.h"

namespace overflow
{
	class AssetPipeline
	{
		friend class Asset;

	public:
		template<typename T>
		static ref<T> GetAsset(UUID uuid)
		{
			auto it = s_Assets.find(uuid);
			if(it == s_Assets.end()) return nullptr;

			return over_cast(T, ref<Asset>(it->second));
		}

		template<typename T, typename... Args>
		static void CreateAsset(UUID uuid, Args&&... args)
		{
			auto it = s_Assets.find(uuid);
			if(it == s_Assets.end())
			{
				T* asset = new T(uuid, std::forward<Args>(args)...);
				s_Assets[asset->m_UUID] = asset;
			}
			else
			{
				it->second->OnReload();
				*it->second = T(uuid, std::forward<Args>(args)...);
			}
		}

	private:
		static std::unordered_map<uint64_t, Asset*> s_Assets;
	};
}

#endif //ASSET_PIPELINE_H

#ifndef ASSET_H
#define ASSET_H

#include "core/utils.h"
#include "AssetPipeline.h"

namespace overflow
{
	class Asset
	{
	public:
		Asset(UUID uuid) : m_UUID(uuid) {}
		virtual ~Asset() { AssetPipeline::s_Assets.erase(m_UUID); }
		UUID GetUUID() { return m_UUID; }

	protected:
		virtual void OnReload() = 0;

	private:
		UUID m_UUID;

		friend class AssetPipeline;
	};
}

#endif //ASSET_H

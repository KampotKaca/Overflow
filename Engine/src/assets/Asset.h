#ifndef ASSET_H
#define ASSET_H

#include "core/utils.h"

namespace overflow
{
	class Asset
	{
	public:
		Asset() = default;
		Asset(UUID uuid) : m_UUID(uuid) {}
		virtual ~Asset() = default;
		
		[[nodiscard]] UUID GetUUID() const { return m_UUID; }

	private:
		UUID m_UUID;
	};
}

#endif //ASSET_H

#include "pch.h"
#include "Asset.h"

namespace overflow
{
	static std::unordered_map<UUID, ref<Asset>> s_Assets;

}
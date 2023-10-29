#ifndef MESH_H
#define MESH_H

#include "core/utils.h"
#include "Asset.h"

namespace overflow
{
	class Mesh : public Asset
	{
	public:
		~Mesh() override = default;
		
		ref<Mesh> Import(const std::filesystem::path& location);
		
	
	protected:
		void OnReload() override;
	
	private:
	};
}

#endif //MESH_H

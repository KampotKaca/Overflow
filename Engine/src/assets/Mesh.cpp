#include "pch.h"
#include "Mesh.h"

namespace overflow
{
	Mesh::Mesh(UUID uuid, std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
		: Asset(uuid), m_Vertices(std::move(vertices)), m_Indices(std::move(indices))
	{
	
	}

	void Mesh::Bind()
	{
	
	}

	void Mesh::UnBind()
	{
	
	}
}
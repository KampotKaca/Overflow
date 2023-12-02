#ifndef MESH_H
#define MESH_H

#include "core/utils.h"
#include "Asset.h"

namespace overflow
{
	struct Vertex
	{
		vec3 Position;
		vec3 Normal;
		vec2 UV;
	};

	class Mesh : public Asset
	{
	public:
		Mesh() = default;
		Mesh(UUID uuid, std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
		~Mesh() override = default;

		void Bind();
		static void UnBind();

	private:

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
	};
}

#endif //MESH_H

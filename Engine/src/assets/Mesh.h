#ifndef MESH_H
#define MESH_H

#include "core/utils.h"
#include "rendering/Buffer.h"

namespace overflow
{
	struct Vertex
	{
		vec3 Position;
		vec3 Normal;
		vec2 UV;
	};

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(UUID uuid, std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
		~Mesh() = default;

		void Bind();
		static void UnBind();

	private:
		UUID m_UUID;

		ref<VAO> m_VAO;
		ref<VBO> m_VBO;
		ref<EBO> m_EBO;

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
	};
}

#endif //MESH_H

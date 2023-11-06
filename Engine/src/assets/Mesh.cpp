#include "pch.h"
#include "Mesh.h"

namespace overflow
{
	Mesh::Mesh(UUID uuid, std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
		: Asset(uuid), m_Vertices(std::move(vertices)), m_Indices(std::move(indices))
	{
		m_VAO = make_ref(VAO);
		m_VAO->Bind();
		m_VBO = make_ref(VBO, m_Vertices.data(), m_Vertices.size());
		m_EBO = make_ref(EBO, m_Indices.data(), m_Indices.size());

		BufferElement position = BufferElement(ShaderDataType::Float3, "Position");
		BufferElement normal = BufferElement(ShaderDataType::Float3, "Normal");
		BufferElement uv = BufferElement(ShaderDataType::Float2, "UV");

		m_VBO->SetLayout(BufferLayout({ position, normal, uv }));
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(m_EBO);

		VAO::Unbind();
	}

	void Mesh::Bind()
	{
		m_VAO->Bind();
		m_VBO->Bind();
		m_EBO->Bind();
	}

	void Mesh::UnBind()
	{
		VAO::Unbind();
		VBO::Unbind();
		EBO::Unbind();
	}
}
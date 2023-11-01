#include "pch.h"
#include "Buffer.h"
#include <glad/glad.h>

namespace overflow
{
	VBO::VBO()
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
	}

	VBO::VBO(uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VBO::VBO(void *vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VBO::~VBO() { glDeleteBuffers(1, &m_RendererID); }
	void VBO::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
	void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	void VBO::SetData(const void *data, uint32_t size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	EBO::EBO() : m_Size(0)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	}

	EBO::EBO(uint32_t *indices, uint32_t size) : m_Size(size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, (int64_t)(size * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
	}

	EBO::~EBO() { glDeleteBuffers(1, &m_RendererID); }

	void EBO::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }
	void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float: case ShaderDataType::Float2:
			case ShaderDataType::Float3: case ShaderDataType::Float4:
			case ShaderDataType::Mat3: case ShaderDataType::Mat4:
				return GL_FLOAT;
			case ShaderDataType::Int: case ShaderDataType::Int2:
			case ShaderDataType::Int3: case ShaderDataType::Int4:
				return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
			case ShaderDataType::None:     break;
		}

		CORE_ASSERT(false, "Unknown ShaderDataType!")
		return 0;
	}

	VAO::VAO()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VAO::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::AddVertexBuffer(const ref<VBO>& vertexBuffer)
	{
		CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!")

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
					                      element.GetComponentCount(),
					                      ShaderDataTypeToOpenGLBaseType(element.Type),
					                      element.Normalized ? GL_TRUE : GL_FALSE,
					                      layout.GetStride(),
					                      (const void*)element.Offset);
					m_VertexBufferIndex++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribIPointer(m_VertexBufferIndex,
					                       element.GetComponentCount(),
					                       ShaderDataTypeToOpenGLBaseType(element.Type),
					                       layout.GetStride(),
					                       (const void*)element.Offset);
					m_VertexBufferIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_VertexBufferIndex);
						glVertexAttribPointer(m_VertexBufferIndex,
						                      count,
						                      ShaderDataTypeToOpenGLBaseType(element.Type),
						                      element.Normalized ? GL_TRUE : GL_FALSE,
						                      layout.GetStride(),
						                      (const void*)(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(m_VertexBufferIndex, 1);
						m_VertexBufferIndex++;
					}
					break;
				}
				default:
					CORE_ASSERT(false, "Unknown ShaderDataType!")
			}
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VAO::SetIndexBuffer(const ref<EBO>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	UBO::UBO(uint32_t size, uint32_t binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	UBO::~UBO() { glDeleteBuffers(1, &m_RendererID); }


	void UBO::SetData(const void* data, uint32_t size, uint32_t offset) const
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}
}
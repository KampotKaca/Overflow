#ifndef BUFFER_H
#define BUFFER_H

#include <utility>

#include "core/utils.h"

namespace overflow
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
			case ShaderDataType::None:     break;
		}

		CORE_ASSERT(false, "Unknown ShaderDataType!")
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type = ShaderDataType::None;
		uint32_t Size = 0;
		size_t Offset = 0;
		bool Normalized = true;

		BufferElement() = default;

		BufferElement(ShaderDataType type, std::string name, bool normalized = false)
				: Name(std::move(name)), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		[[nodiscard]] int GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3; // 3* float3
				case ShaderDataType::Mat4:    return 4; // 4* float4
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
				case ShaderDataType::None:    break;
			}

			CORE_ASSERT(false, "Unknown ShaderDataType!")
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(std::initializer_list<BufferElement> elements)
				: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		[[nodiscard]] int GetStride() const { return (int)m_Stride; }
		[[nodiscard]] const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		[[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		[[nodiscard]] std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VBO
	{
	public:
		VBO(uint32_t size);
		VBO(float* vertices, uint32_t size);
		~VBO();

		void Bind() const;
		static void Unbind();

		void SetData(const void *data, uint32_t size) const;

		[[nodiscard]] const BufferLayout &GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout &layout) { m_Layout = layout; }

	private:
		uint32_t m_RendererID = 0;
		BufferLayout m_Layout;
	};

	class EBO
	{
	public:
		EBO(uint32_t* indices, uint32_t size);
		~EBO();

		void Bind() const;
		static void Unbind() ;

		[[nodiscard]] uint32_t Size() const { return m_Size; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Size;
	};

	class VAO
	{
	public:
		VAO();
		~VAO();

		void Bind() const;
		static void Unbind() ;

		void AddVertexBuffer(const ref<VBO>& vertexBuffer);
		void SetIndexBuffer(const ref<EBO>& indexBuffer);

		[[nodiscard]] const std::vector<ref<VBO>>& GetVertexBuffers() const { return m_VertexBuffers; }
		[[nodiscard]] const ref<EBO>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<ref<VBO>> m_VertexBuffers;
		ref<EBO> m_IndexBuffer;
	};

	class UBO
	{
	public:
		UBO(uint32_t size, uint32_t binding);
		~UBO();

		void SetData(const void* data, uint32_t size, uint32_t offset = 0) const;
	private:
		uint32_t m_RendererID = 0;
	};
}

#endif //BUFFER_H

#ifndef TEX2D_H
#define TEX2D_H

#include "core/utils.h"

namespace overflow
{
	class Tex2D
	{
	public:
		Tex2D() = default;
		Tex2D(UUID uuid, byte* data, vec2i size,
			  int numColCh, int filter = GL_LINEAR,
			  int wrap = GL_REPEAT, bool mipmaps = true);
		~Tex2D() { glDeleteTextures(1, &m_TexID); }

		void Bind(int texUnit) const
		{
			glActiveTexture(texUnit + GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_TexID);
		}

		[[nodiscard]] UUID GetUUID()const { return m_UUID; }
		[[nodiscard]] vec2i Size()const { return m_Size; }
		[[nodiscard]] int NumChannels()const { return m_NumColCh; }
		[[nodiscard]] uint32_t TexID()const { return m_TexID; }
		[[nodiscard]] int NumColorChannels() const { return m_NumColCh; }
		[[nodiscard]] int Filter() const { return m_Filter; }
		[[nodiscard]] int Wrap() const { return m_Wrap; }
		[[nodiscard]] bool MipMaps() const { return m_MipMaps; }

	private:
		UUID m_UUID;
		uint32_t m_TexID = 0;
		vec2i m_Size = vec2i();
		int m_NumColCh = 0, m_Filter = GL_LINEAR, m_Wrap = GL_REPEAT;
		bool m_MipMaps = true;
	};
}

#endif //TEX2D_H

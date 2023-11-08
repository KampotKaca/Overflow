#include "pch.h"
#include "Tex2D.h"

namespace overflow
{
	Tex2D::Tex2D(UUID uuid, byte* data, vec2i size,
				 int numColCh, int filter, int wrap, bool mipmaps)
				 : Asset(uuid), m_Size(size), m_NumColCh(numColCh),
				 m_Filter(filter), m_Wrap(wrap), m_MipMaps(mipmaps)
	{
		glGenTextures(1, &m_TexID);
		glBindTexture(GL_TEXTURE_2D, m_TexID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Size.x, m_Size.y, 0,
		             GL_RGBA8, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

		if(wrap == GL_CLAMP_TO_BORDER)
		{
			float _colors[] = { 1, 1, 1, 1 };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, _colors);
		}

		if(mipmaps) glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
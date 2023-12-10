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

		int format = GL_R;
		int iFormat = GL_R;
		switch (m_NumColCh)
		{
			case 2:
				format = GL_RG;
				iFormat = GL_RG8;
			break;
			case 3:
				format = GL_RGB;
				iFormat = GL_RGB8;
				break;
			case 4:
				format = GL_RGBA;
				iFormat = GL_RGBA8;
				break;
		}
		
		glTexImage2D(GL_TEXTURE_2D, 0, iFormat, m_Size.x, m_Size.y, 0, format, GL_UNSIGNED_BYTE, data);
		
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
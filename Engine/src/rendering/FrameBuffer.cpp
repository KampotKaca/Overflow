#include "pch.h"
#include "FrameBuffer.h"

namespace overflow
{
	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace utils
	{
		static GLenum TexTarget(bool multiSampled)
		{ return multiSampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D; }

		static void CreateTextures(bool multiSampled, uint32_t* outID, int32_t count)
		{ glCreateTextures(TexTarget(multiSampled), count, outID); }

		static void BindTexture(bool multiSampled, uint32_t id)
		{ glBindTexture(TexTarget(multiSampled), id); }

		static void AttachColorTex(uint32_t id, int samples, int32_t internalFormat,
		                           GLenum format, int32_t width, int32_t height, int index)
		{
			bool multiSampled = samples > 1;
			if (multiSampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TexTarget(multiSampled), id, 0);
		}

		static void AttachDepthTex(uint32_t id, int samples, GLenum format, GLenum attachmentType,
		                           int32_t width, int32_t height)
		{
			bool multiSampled = samples > 1;
			if (multiSampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TexTarget(multiSampled), id, 0);
		}

		static bool IsDepthFormat(FBTexFormat format)
		{
			switch (format)
			{
				case FBTexFormat::DEPTH24STENCIL8: return true;
				default: return false;
			}
		}

		static GLenum TexFormatToGL(FBTexFormat format)
		{
			switch (format)
			{
				case FBTexFormat::RGBA8:       return GL_RGBA8;
				case FBTexFormat::RED_INTEGER: return GL_RED_INTEGER;
				default: return 0;
			}
		}
	}

	FrameBuffer::FrameBuffer(FBSpecification spec)
			: m_Spec(std::move(spec))
	{
		for (auto& sp : m_Spec.Attachments.Attachments)
		{
			if (!utils::IsDepthFormat(sp.TextureFormat))
				m_ColorSpec.emplace_back(sp);
			else
				m_DepthSpec = sp;
		}

		Invalidate();
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures((int32_t)m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void FrameBuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures((int32_t)m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multisample = m_Spec.Samples > 1;

		// Attachments
		if (!m_ColorSpec.empty())
		{
			m_ColorAttachments.resize(m_ColorSpec.size());
			utils::CreateTextures(multisample, m_ColorAttachments.data(), (int32_t)m_ColorAttachments.size());

			for (int32_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				utils::BindTexture(multisample, m_ColorAttachments[i]);
				switch (m_ColorSpec[i].TextureFormat)
				{
					case FBTexFormat::RGBA8:
						utils::AttachColorTex(m_ColorAttachments[i], (int32_t)m_Spec.Samples,
						                      GL_RGBA8, GL_RGBA,
						                      (int32_t)m_Spec.Width, (int32_t)m_Spec.Height, i);
						break;
					case FBTexFormat::RED_INTEGER:
						utils::AttachColorTex(m_ColorAttachments[i], (int32_t)m_Spec.Samples,
						                      GL_R32I, GL_RED_INTEGER,
						                      (int32_t)m_Spec.Width, (int32_t)m_Spec.Height, i);
						break;
					default: break;
				}
			}
		}

		if (m_DepthSpec.TextureFormat != FBTexFormat::None)
		{
			utils::CreateTextures(multisample, &m_DepthAttachment, 1);
			utils::BindTexture(multisample, m_DepthAttachment);
			switch (m_DepthSpec.TextureFormat)
			{
				default: break;
				case FBTexFormat::DEPTH24STENCIL8:
					utils::AttachDepthTex(m_DepthAttachment, (int32_t)m_Spec.Samples,
					                      GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT,
					                      (int32_t)m_Spec.Width, (int32_t)m_Spec.Height);
					break;
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			CORE_ASSERT(m_ColorAttachments.size() <= 4, "Not Enough color attachments!!!")
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((int32_t)m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty()) glDrawBuffer(GL_NONE);

		CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!")

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, (int32_t)m_Spec.Width, (int32_t)m_Spec.Height);
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Spec.Width = width;
		m_Spec.Height = height;

		Invalidate();
	}

	int FrameBuffer::ReadPixel(uint32_t id, uint32_t x, uint32_t y)
	{
		CORE_ASSERT(id < m_ColorAttachments.size(), "Index out of the range!!!")

		glReadBuffer(GL_COLOR_ATTACHMENT0 + id);
		int pixelData;
		glReadPixels((int32_t)x, (int32_t)y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void FrameBuffer::ClearAttachment(uint32_t id, uint32_t value)
	{
		CORE_ASSERT(id < m_ColorAttachments.size(), "Index out of the range!!!")

		auto& spec = m_ColorSpec[id];
		glClearTexImage(m_ColorAttachments[id], 0,
		                utils::TexFormatToGL(spec.TextureFormat), GL_INT, &value);
	}
	
	FBSpecification FBSpecification::Default()
	{
		FBSpecification fbSpec;
		fbSpec.Attachments = { FBTexSpecification(FBTexFormat::RGBA8),
		                       FBTexSpecification(FBTexFormat::RED_INTEGER),
		                       FBTexSpecification(FBTexFormat::Depth) };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		return fbSpec;
	}
}
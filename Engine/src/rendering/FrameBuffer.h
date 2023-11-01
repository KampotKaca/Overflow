#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "core/utils.h"

namespace overflow
{
    enum class FBTexFormat
    {
        None, RGBA8, RED_INTEGER, DEPTH24STENCIL8, Depth = DEPTH24STENCIL8
    };

    struct FBTexSpecification
    {
        FBTexSpecification() = default;
        explicit FBTexSpecification(FBTexFormat format) : TextureFormat(format) {}

        FBTexFormat TextureFormat = FBTexFormat::None;
    };

    struct FBAttachmentSpecification
    {
        FBAttachmentSpecification() = default;
        FBAttachmentSpecification(std::initializer_list<FBTexSpecification> attachments)
                : Attachments(attachments) {}

        std::vector<FBTexSpecification> Attachments;
    };

    struct FBSpecification
    {
		static FBSpecification Default();
        uint32_t Width = 0, Height = 0;
        FBAttachmentSpecification Attachments;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class FrameBuffer
    {
    public:
	    explicit FrameBuffer(FBSpecification spec);
	    ~FrameBuffer();

	    void Invalidate();

	    void Bind() const;
	    static void UnBind();
	    void Resize(uint32_t width, uint32_t height);
	    int ReadPixel(uint32_t id, uint32_t x, uint32_t y);
	    void ClearAttachment(uint32_t id, uint32_t value);
	    [[nodiscard]] uint32_t GetColorAttachmentRendererID(uint32_t id) const
	    { CORE_ASSERT(id < m_ColorAttachments.size(), "Index out of the range!!!") return m_ColorAttachments[id]; }

		const FBSpecification& GetSpecification() { return m_Spec; }

    private:
	    uint32_t m_RendererID = 0;
	    FBSpecification m_Spec;

	    std::vector<FBTexSpecification> m_ColorSpec;
	    FBTexSpecification m_DepthSpec = FBTexSpecification(FBTexFormat::None);

	    std::vector<uint32_t> m_ColorAttachments;
	    uint32_t m_DepthAttachment = 0;
    };
}

#endif //FRAMEBUFFER_H

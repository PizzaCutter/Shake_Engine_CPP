#pragma once
#include "Shake/Renderer/FrameBuffer.h"

namespace Shake
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FramebufferSpecifications& spec);
        virtual ~OpenGLFrameBuffer();

        void Invalidate();
        void Bind() override;
        void Unbind() override;
        void Resize(int32_t width, int32_t height) override;
        
        virtual uint32_t GetColorAttachmentRendererID() const; 
        
        const FramebufferSpecifications& GetSpecification() const override;

    private:
        uint32_t m_rendererID;
        uint32_t m_colorAttachment;
        uint32_t m_depthAttachment;
        
        FramebufferSpecifications m_frameBufferSpecification;
    };
}

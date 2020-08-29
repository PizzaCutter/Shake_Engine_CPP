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
        
        virtual uint32_t GetColorAttachmentRendererID() const; 
        
        const FramebufferSpecifications& GetSpecification() const override;

    private:
        uint32_t m_rendererID;
        uint32_t m_colorAttachment;
        uint32_t m_depthAttachment;
        
        FramebufferSpecifications m_frameBufferSpecification;
    };
}

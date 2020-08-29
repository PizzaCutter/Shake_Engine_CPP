#pragma once
#include "Shake/Core/Core.h"

namespace Shake
{
    struct FramebufferSpecifications
    {
        uint32_t width, height;
        uint32_t samples = 1;

        bool swapChainTarget = false;
    };
    
    class FrameBuffer
    {
    public:
        virtual const FramebufferSpecifications& GetSpecification() const = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;

        static Ref<FrameBuffer> Create(const FramebufferSpecifications& spec);
    };
}

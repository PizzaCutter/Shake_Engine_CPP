#pragma once
#include "Shake/Core/Core.h"
#include "Shake/Math/SMath.h"

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
        virtual ~FrameBuffer() {};

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(int32_t width, int32_t height) = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;
        virtual const FramebufferSpecifications& GetSpecification() const = 0;

        static Ref<FrameBuffer> Create(const FramebufferSpecifications& spec);
    };
}

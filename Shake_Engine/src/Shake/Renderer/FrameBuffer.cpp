#include "sepch.h"
#include "FrameBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Shake
{
Ref<FrameBuffer> FrameBuffer::Create(const FramebufferSpecifications& spec)
{
    switch (Renderer::GetRenderAPI())
    {
    case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
    case RenderAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>(spec);
    }
    return nullptr;
}

}

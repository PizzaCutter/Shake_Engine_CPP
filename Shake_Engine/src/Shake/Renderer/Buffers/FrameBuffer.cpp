#include "sepch.h"
#include "FrameBuffer.h"

#include "Shake/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Shake
{
SharedPtr<FrameBuffer> FrameBuffer::Create(const FramebufferSpecifications& spec)
{
    switch (Renderer::GetRenderAPI())
    {
    case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
    case RenderAPI::API::OpenGL: return CreateSharedPtr<OpenGLFrameBuffer>(spec);
    }
    return nullptr;
}

}

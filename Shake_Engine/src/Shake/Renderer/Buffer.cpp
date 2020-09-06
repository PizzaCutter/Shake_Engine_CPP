#include "sepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Shake/Core/Core.h"


namespace Shake
{
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
        case RenderAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(size);
        }
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
        case RenderAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        default: SE_CORE_ASSERT(false, "Unknown render api");
        }
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
        case RenderAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
        default: SE_CORE_ASSERT(false, "Unknown render api");
        }
        return nullptr;
    }
}

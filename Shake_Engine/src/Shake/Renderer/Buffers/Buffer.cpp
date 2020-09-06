#include "sepch.h"
#include "Buffer.h"

#include "Shake/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Shake/Core/Core.h"


namespace Shake
{
    SharedPtr<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
        case RenderAPI::API::OpenGL: return CreateSharedPtr<OpenGLVertexBuffer>(size);
        }
        return nullptr;
    }

    SharedPtr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
        case RenderAPI::API::OpenGL: return CreateSharedPtr<OpenGLVertexBuffer>(vertices, size);
        default: SE_CORE_ASSERT(false, "Unknown render api");
        }
        return nullptr;
    }

    SharedPtr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
        case RenderAPI::API::OpenGL: return CreateSharedPtr<OpenGLIndexBuffer>(indices, count);
        default: SE_CORE_ASSERT(false, "Unknown render api");
        }
        return nullptr;
    }
}

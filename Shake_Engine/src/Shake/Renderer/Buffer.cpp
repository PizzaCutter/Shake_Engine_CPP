#include "sepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Shake/Core/Core.h"
#include "Shake/Core/Log.h"


namespace Shake
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
       switch(Renderer::GetRenderAPI())
       {
            case RenderAPI::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
            case RenderAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
            default: SE_CORE_ASSERT(false, "Unknown render api");
       }
       return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch(Renderer::GetRenderAPI())
        {
        case RenderAPI::None: SE_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
        case RenderAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
        default: SE_CORE_ASSERT(false, "Unknown render api");
        }
        return nullptr;
    }
}

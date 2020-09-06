#include "sepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Shake/Core/Core.h"

namespace Shake
{
    SharedPtr<VertexArray> VertexArray::Create()
    {
        switch(Renderer::GetRenderAPI())
        {
           case RenderAPI::API::None: SE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
           case RenderAPI::API::OpenGL: return CreateSharedPtr<OpenGLVertexArray>(OpenGLVertexArray());
        }

        SE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}

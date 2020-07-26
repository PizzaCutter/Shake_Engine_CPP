#include "sepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Shake/Core/Core.h"
#include "Shake/Core/Log.h"


namespace Shake
{
    VertexArray* VertexArray::Create()
    {
        switch(Renderer::GetRenderAPI())
        {
           case RenderAPI::None: SE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
           case RenderAPI::OpenGL: return new OpenGLVertexArray();
        }

        SE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}

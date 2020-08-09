#include "sepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Shake/Core/Core.h"
#include "Shake/Core/Log.h"

namespace Shake
{
    Shader* Shader::Create(const std::string& path)
    {
         switch(Renderer::GetRenderAPI())
         {
         case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI:::None is currently not supported")
             break;
         case RenderAPI::API::OpenGL: return new OpenGLShader(path);
         default: ;
         }
         return nullptr;
    }
}

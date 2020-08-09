#include "sepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Shake/Core/Core.h"
#include "Shake/Core/Log.h"

namespace Shake
{
    Ref<Shader> Shader::Create(const std::string& path)
    {
         switch(Renderer::GetRenderAPI())
         {
         case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI:::None is currently not supported")
             break;
         case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
         default: ;
         }
         return nullptr;
    }

    void ShaderLibrary::Load(const std::string& filepath)
    {
        Ref<Shader> shader = Shader::Create(filepath);
        const auto foundIterator = m_shaderReferences.find(shader->GetName());
        SE_CORE_ASSERT(foundIterator == m_shaderReferences.end(), "Shader already loaded");
        m_shaderReferences.emplace(shader->GetName(), shader); 
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& shaderName)
    {
        const auto foundIterator = m_shaderReferences.find(shaderName);
        SE_CORE_ASSERT(foundIterator != m_shaderReferences.end(), "Shader does not exist");
        return foundIterator->second;
    }
}

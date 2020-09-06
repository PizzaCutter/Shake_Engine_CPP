#include "sepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Shake/Core/Core.h"

namespace Shake
{
    SharedPtr<Shader> Shader::Create(const SString& path)
    {
         switch(Renderer::GetRenderAPI())
         {
         case RenderAPI::API::None: SE_CORE_ASSERT(false, "RenderAPI:::None is currently not supported")
             break;
         case RenderAPI::API::OpenGL: return CreateSharedPtr<OpenGLShader>(path);
         default: ;
         }
         return nullptr;
    }

    void ShaderLibrary::Load(const SString& filepath)
    {
        SharedPtr<Shader> shader = Shader::Create(filepath);
        const auto foundIterator = m_shaderReferences.find(shader->GetName());
        SE_CORE_ASSERT(foundIterator == m_shaderReferences.end(), "Shader already loaded");
        m_shaderReferences.emplace(shader->GetName(), shader); 
    }

    SharedPtr<Shader> ShaderLibrary::Get(const SString& shaderName)
    {
        const auto foundIterator = m_shaderReferences.find(shaderName);
        SE_CORE_ASSERT(foundIterator != m_shaderReferences.end(), "Shader does not exist");
        return foundIterator->second;
    }
}

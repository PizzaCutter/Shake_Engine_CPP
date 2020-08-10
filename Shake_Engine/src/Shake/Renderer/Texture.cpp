#include "sepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Shake/Core/Log.h"

namespace Shake
{
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch(Renderer::GetRenderAPI())
        {
           case RenderAPI::API::None: break;
            case RenderAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(width, height);
        }
        
        SE_CORE_ASSERT(static_cast<int>(Renderer::GetRenderAPI()), "Could not create texture since current RenderAPI is not supported");
        return nullptr;
    }
    
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch(Renderer::GetRenderAPI())
        {
        case RenderAPI::API::None: break;
        case RenderAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(path);
        }

        SE_CORE_ASSERT(static_cast<int>(Renderer::GetRenderAPI()), "Could not create texture since current RenderAPI is not supported");
        return nullptr;
    }
}

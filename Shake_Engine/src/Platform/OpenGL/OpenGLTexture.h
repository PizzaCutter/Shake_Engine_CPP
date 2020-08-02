#pragma once
#include "Shake/Core/Core.h"
#include "Shake/Renderer/Texture.h"

namespace Shake
{
    class OpenGLTexture : public Texture2D
    {
    public:
        OpenGLTexture(const std::string& path);
        ~OpenGLTexture();
        
        int32_t GetWidth() const override { return m_width; };
        int32_t GetHeight() const override { return m_height; };
        unsigned int GetRendererId() const { return m_rendererId; }
        
        void Bind(int32_t slot = 0) override;
    private:
        std::string m_path = "";
        
        unsigned int m_width = 0;
        unsigned int m_height = 0;

        unsigned int m_rendererId = 0;
    };
}


#pragma once
#include "Shake/Core/Core.h"
#include "Shake/Renderer/Textures/Texture.h"

namespace Shake
{
    class OpenGLTexture : public Texture2D
    {
    public:
        OpenGLTexture(uint32_t width, uint32_t height);
        OpenGLTexture(const SString& path);
        ~OpenGLTexture();
        
        int32_t GetWidth() const override { return m_width; };
        int32_t GetHeight() const override { return m_height; };
        uint32_t GetRendererID() const override { return m_rendererId; }

        void SetData(void* data, int32_t size) override;
        void Bind(int32_t slot = 0) override;

        bool operator==(const Texture& other) override
        {
            // ReSharper disable once CppCStyleCast
            return m_rendererId == ((OpenGLTexture&)other).GetRendererID();  
        }
    private:
        SString m_path = "";
        
        unsigned int m_width = 0;
        unsigned int m_height = 0;

        unsigned int m_rendererId = 0;
    };
}


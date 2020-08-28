#include "sepch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"
#include "Shake/Core/Log.h"

namespace Shake
{
    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
        : m_width(width), m_height(height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererId);
        glTextureStorage2D(m_rendererId, 1, GL_RGBA8, m_width, m_height);

        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    }

    OpenGLTexture::OpenGLTexture(const std::string& path)
        : m_path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        
        m_width = width;
        m_height = height;

        SE_CORE_ASSERT(data, "COULD NOT LOAD TEXTURE");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererId);
        glTextureStorage2D(m_rendererId, 1, channels == 4 ? GL_RGBA8 : GL_RGB8, m_width, m_height);

        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_rendererId, 0, 0, 0, m_width, m_height, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteBuffers(1, &m_rendererId); 
    }

    void OpenGLTexture::SetData(void* data, int32_t size)
    {
        glTextureSubImage2D(m_rendererId, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data); 
    }

    void OpenGLTexture::Bind(int32_t slot)
    {
        glBindTextureUnit(slot, m_rendererId);
    }
}

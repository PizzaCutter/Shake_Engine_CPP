#include "sepch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"
#include <GL/gl.h>

namespace Shake
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
    {
        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
       glDeleteBuffers(1, &m_rendererID); 
    }

    void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void OpenGLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void OpenGLVertexBuffer::UnBind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
    {
        m_bufferLayout = layout;     
    }

    const BufferLayout& OpenGLVertexBuffer::GetBufferLayout() const
    {
        return m_bufferLayout;      
    }

    // --------------------- INDEX BUFFER ---------------------------

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
        : m_count(count)
    {
        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_rendererID); 
    }

    void OpenGLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    }

    void OpenGLIndexBuffer::UnBind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

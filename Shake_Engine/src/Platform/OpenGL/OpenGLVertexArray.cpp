#include "sepch.h"
#include "OpenGLVertexArray.h"

#include <vector>
#include "glad/glad.h"

namespace Shake
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::None: return GL_FLOAT;
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3: return GL_FLOAT;
        case ShaderDataType::Mat4: return GL_FLOAT;
        case ShaderDataType::Int: return GL_INT;
        case ShaderDataType::Int2: return GL_INT;
        case ShaderDataType::Int3: return GL_INT;
        case ShaderDataType::Int4: return GL_INT;
        case ShaderDataType::Bool: return GL_BOOL;
        default: ;
        }

        // TODO[rsmekens]: add dev exception
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_rendererId);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererId);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_rendererId);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& newVertexBuffer) 
    {
        glBindVertexArray(m_rendererId);
        newVertexBuffer->Bind();

        //TODO[rsmekens]: add assert when vertex buffer is empty

        uint32_t index = 0;
        const auto& layout = newVertexBuffer->GetBufferLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.m_type),
                                  element.m_normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  reinterpret_cast<const void*>(element.m_offset));
            index++;
        }
        
        m_vertexBuffers.push_back(newVertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_rendererId);
        indexBuffer->Bind();

        m_indexBuffer = indexBuffer;
    }
}

#pragma once

#include <memory>

#include "Shake/Core/Core.h"
#include "Shake/Renderer/VertexArray.h"

namespace Shake
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() const override;
        void UnBind() const override;
        
        void AddVertexBuffer(const SharedPtr<VertexBuffer>& newVertexBuffer) override;
        void SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer) override;

        const std::vector<SharedPtr<VertexBuffer>>& GetVertexBuffer() const override { return m_vertexBuffers; };
        const SharedPtr<IndexBuffer>& GetIndexBuffer() const override { return m_indexBuffer; };
        
    private:
       uint32_t m_rendererId; 
       std::vector<SharedPtr<VertexBuffer>> m_vertexBuffers;
       SharedPtr<IndexBuffer> m_indexBuffer;
    };
}

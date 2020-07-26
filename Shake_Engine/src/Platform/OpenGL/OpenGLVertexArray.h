#pragma once

#include <memory>
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
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& newVertexBuffer) override;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override { return m_vertexBuffers; };
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_indexBuffer; };
        
    private:
       uint32_t m_rendererId; 
       std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
       std::shared_ptr<IndexBuffer> m_indexBuffer;
    };
}

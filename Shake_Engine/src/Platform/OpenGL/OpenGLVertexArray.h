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
        void AddVertexBuffer(const Ref<VertexBuffer>& newVertexBuffer) override;
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override { return m_vertexBuffers; };
        const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_indexBuffer; };
        
    private:
       uint32_t m_rendererId; 
       std::vector<Ref<VertexBuffer>> m_vertexBuffers;
       Ref<IndexBuffer> m_indexBuffer;
    };
}

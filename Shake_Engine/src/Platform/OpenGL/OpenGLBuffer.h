#pragma once
#include "Shake/Renderer/Buffers/Buffer.h"

namespace Shake
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();
        
        void SetData(const void* data, uint32_t size) override;
        
        void Bind() override;
        void UnBind() override;

        void SetLayout(const BufferLayout& layout) override;
        const BufferLayout& GetBufferLayout() const override;
    private:
        uint32_t m_rendererID;
        BufferLayout m_bufferLayout;
    };

    class OpenGLIndexBuffer : public IndexBuffer 
        {
        public:
            OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
            virtual ~OpenGLIndexBuffer();
            
            void Bind() override;
            void UnBind() override;

            uint32_t GetCount() const override { return m_count; }
        private:
            uint32_t m_rendererID;
            uint32_t m_count;
        };
}


#pragma once
#include "Shake/Renderer/Buffer.h"

namespace Shake
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();
        
        void Bind() override;
        void UnBind() override;

    private:
        uint32_t m_rendererID; 
    };

    class OpenGLIndexBuffer : public IndexBuffer 
        {
        public:
            OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
            virtual ~OpenGLIndexBuffer();
            
            void Bind() override;
            void UnBind() override;

            uint32_t GetCount() const { return m_count; }
        private:
            uint32_t m_rendererID;
            uint32_t m_count;
        };
}


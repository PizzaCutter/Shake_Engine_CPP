#pragma once

#include "Shake/Core/Core.h"
#include "Shake/Renderer/Buffers/Buffer.h"

namespace Shake
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void AddVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<SharedPtr<VertexBuffer>>& GetVertexBuffer() const = 0;
        virtual const SharedPtr<IndexBuffer>& GetIndexBuffer() const = 0;

        static SharedPtr<VertexArray> Create();
    };
}

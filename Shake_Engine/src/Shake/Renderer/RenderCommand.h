#pragma once
#include "RenderAPI.h"
#include "Renderer2D.h"

namespace Shake
{
    class VertexArray;

    class RenderCommand
    {
    public:
        inline static void SetClearColor(const glm::vec4& color)
        {
            s_renderAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            s_renderAPI->Clear();
        }

        inline static void Initialize()
        {
            s_renderAPI->Initialize();
            Renderer2D::Initialize();
        }

        inline static void WindowResize(int32_t width, int32_t height)
        {
            s_renderAPI->WindowResize(width, height); 
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
        {
            s_renderAPI->DrawIndexed(vertexArray, indexCount);
        }

    private:
        static RenderAPI* s_renderAPI;
    };
}

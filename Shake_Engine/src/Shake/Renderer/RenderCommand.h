#pragma once
#include "RenderAPI.h"

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

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            s_renderAPI->DrawIndexed(vertexArray);
        }

    private:
        static RenderAPI* s_renderAPI;
    };
}

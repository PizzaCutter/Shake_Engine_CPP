#pragma once
#include "Shake/Core/Core.h"
#include "Shake/Renderer/RenderAPI.h"

namespace Shake
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}

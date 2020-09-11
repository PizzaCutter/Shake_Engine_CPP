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
        void Initialize() override;
        void WindowResize(int32_t width, int32_t height) override;
        void DrawIndexed(const SharedPtr<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
        void RenderFrameBuffer(const SharedPtr<FrameBuffer>& frameBuffer) override;
    };
}

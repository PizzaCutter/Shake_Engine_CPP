#pragma once
#include "RenderAPI.h"

namespace Shake
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        
        inline static RenderAPI::API GetRenderAPI() { return RenderAPI::GetAPI(); };
    };
}

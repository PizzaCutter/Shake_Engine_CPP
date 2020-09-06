#pragma once

#include <glm/glm.hpp>

#include "Shake/Core/Core.h"

namespace Shake
{
    class VertexArray;

    class RenderAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1
        };
    public:
        virtual ~RenderAPI() {};
        
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void Initialize() = 0;

        virtual void WindowResize(int32_t width, int32_t height) = 0;

        virtual void DrawIndexed(const SharedPtr<VertexArray>& vertexArray, uint32_t indexCount) = 0;

        inline static API GetAPI() { return s_api; }
    private:
        static API s_api;
    };
}

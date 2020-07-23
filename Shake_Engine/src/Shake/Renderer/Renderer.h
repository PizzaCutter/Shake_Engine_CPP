#pragma once

namespace Shake
{
    enum class RenderAPI
    {
        None = 0,
        OpenGL = 1
    };

    class Renderer
    {
    public:
        static inline RenderAPI GetRenderAPI() { return s_rendererAPI; };
        
    private:
        static RenderAPI s_rendererAPI;
    };
}
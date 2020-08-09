#pragma once
#include "Shake/Core/Core.h"
#include "Shake/Math/SMath.h"

namespace Shake
{
    class Shader;
    class VertexArray;
    class OrthographicCamera;

    struct Renderer2DStorage
    {
        Ref<VertexArray> m_vertexArray;
        Ref<Shader> m_flatShader;
    };

    class Renderer2D
    {
    public:
        static void Initialize();
        static void Shutdown();
        
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(const SVector3& position, const SVector2& size, const SVector4& color);

       static Renderer2DStorage* m_rendererStorage; 
    };
}

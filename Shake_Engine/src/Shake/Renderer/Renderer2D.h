#pragma once
#include "Shake/Core/Core.h"
#include "Shake/Math/SMath.h"

namespace Shake
{
    class Texture2D;
    class Shader;
    class VertexArray;
    class OrthographicCamera;

    struct Renderer2DStorage
    {
        Ref<VertexArray> m_vertexArray;
        Ref<Shader> m_textureShader;
        Ref<Texture2D> m_whiteTexture;
    };

    class Renderer2D
    {
    public:
        static void Initialize();
        static void Shutdown();
        
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(const SVector3& position, const SVector2& size, const SVector4& color);
        static void DrawRotatedQuad(const SVector3& position, const SVector2& size, float rotation, const SVector4& color = SVector4(1.0f, 1.0f, 1.0f, 1.0f));
        
        static void DrawQuadTextured(const SVector3& position, const SVector2& size, const Ref<Texture2D> texture, const SVector4& color = {1.0f, 1.0f, 1.0f, 1.0f}, const SVector2& tilingSize = {1.0f, 1.0f});
        static void DrawRotatedQuadTextured(const SVector3& position, const SVector2& size, float rotation, const Ref<Texture2D> texture, const SVector2& tilingSize = {1.0f, 1.0f} , const SVector4& color = {1.0f, 1.0f, 1.0f, 1.0f});

       static Renderer2DStorage* m_rendererStorage; 
    };
}

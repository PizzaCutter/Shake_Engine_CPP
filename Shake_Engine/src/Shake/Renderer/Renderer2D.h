#pragma once
#include "Shake/Core/Core.h"
#include "Shake/Math/SMath.h"

namespace Shake
{
    class SubTexture2D;
    class Texture2D;
    class Shader;
    class VertexArray;
    class VertexBuffer;
    class OrthographicCamera;

    struct QuadVertex
    {
        SVector3 m_position;
        SVector4 m_color;
        SVector2 m_texCoord;
        float m_textureSlot;
        SVector2 m_tillingSize;
    };

    struct Renderer2DStorage
    {
        const uint32_t MaxQuads = 10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
        static const uint32_t MaxTextureSlots = 32;
        
        Ref<VertexArray> m_vertexArray;
        Ref<VertexBuffer> m_vertexBuffer;
        
        Ref<Shader> m_textureShader;
        Ref<Texture2D> m_whiteTexture;

        uint32_t m_quadIndexCount = 0;
        QuadVertex* m_quadVertexBufferBase = nullptr;
        QuadVertex* m_quadVertexBufferPtr = nullptr;

        uint32_t m_textureSlotIndexCount = 1;
        std::array<Ref<Texture2D>, MaxTextureSlots> m_textures;

        SVector4 m_vertices[4];
    };

    struct RenderStatistics
    {
        uint32_t BatchCount = 0;
        uint32_t QuadCount = 0;
        uint32_t IndexCount = 0;
        uint32_t TextureCount = 0;
    };

    class Renderer2D
    {
    public:
        static void Initialize();
        static void Shutdown();
        
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Flush();
        // When we have reached maximum quad count we render and then start a new batch
        static void FlushAndReset();

        static void DrawQuad(const SVector3& position, const SVector2& size, const SVector4& color);
        static void DrawRotatedQuad(const SVector3& position, const SVector2& size, float rotation, const SVector4& color = SVector4(1.0f, 1.0f, 1.0f, 1.0f));
        
        static void DrawQuadTextured(const SVector3& position, const SVector2& size, const Ref<Texture2D> texture, const SVector4& color = {1.0f, 1.0f, 1.0f, 1.0f}, const SVector2& tilingSize = {1.0f, 1.0f});
        static void DrawQuadSubTexture(const SVector3& position, const SVector2& size, const Ref<SubTexture2D> subTexture2D, const SVector4& color, const SVector2& tilingSize = {1.0f, 1.0f});        
        static void DrawRotatedQuadTextured(const SVector3& position, const SVector2& size, float rotation, const Ref<Texture2D> texture, const SVector2& tilingSize = {1.0f, 1.0f} , const SVector4& color = {1.0f, 1.0f, 1.0f, 1.0f});

        static RenderStatistics GetRenderStats();

        static Renderer2DStorage m_rendererStorage;
        static RenderStatistics m_rendererStatistics;
    };
}

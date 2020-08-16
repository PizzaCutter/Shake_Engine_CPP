#include "sepch.h"
#include "Renderer2D.h"


#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Camera/OrthographicCamera.h"

namespace Shake
{
    Renderer2DStorage Renderer2D::m_rendererStorage = Renderer2DStorage();

    void Renderer2D::Initialize()
    {
        m_rendererStorage.m_vertexArray = VertexArray::Create();

        m_rendererStorage.m_vertexBuffer = VertexBuffer::Create(m_rendererStorage.MaxVertices * sizeof(QuadVertex));
        const BufferLayout layout = {
            {"a_position", ShaderDataType::Float3},
            {"a_color", ShaderDataType::Float4},
            {"a_texcoord", ShaderDataType::Float2},
            {"a_textureslot", ShaderDataType::Float}
        };
        m_rendererStorage.m_vertexBuffer->SetLayout(layout);
        m_rendererStorage.m_vertexArray->AddVertexBuffer(m_rendererStorage.m_vertexBuffer);

        m_rendererStorage.m_quadVertexBufferBase = new QuadVertex[m_rendererStorage.MaxVertices];

        // SETTING UP INDEX BUFFER
        uint32_t* indices = new uint32_t[m_rendererStorage.MaxIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < m_rendererStorage.MaxIndices; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        const Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, m_rendererStorage.MaxIndices);
        m_rendererStorage.m_vertexArray->SetIndexBuffer(indexBuffer);
        delete[] indices;

        // Creating white texture for rendering just color quads
        m_rendererStorage.m_whiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        m_rendererStorage.m_whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
        m_rendererStorage.m_textures[0] = m_rendererStorage.m_whiteTexture;

        // SETTING UP DEFAULT TEXTURE SHADER
        m_rendererStorage.m_textureShader = Shader::Create("Content/Shaders/Texture.glsl");
        m_rendererStorage.m_textureShader->Bind();
        int32_t samplerSlots[m_rendererStorage.MaxTextureSlots];
        for (int i = 0; i < m_rendererStorage.MaxTextureSlots; ++i)
        {
            samplerSlots[i] = i; 
        }
        m_rendererStorage.m_textureShader->UploadUniformIntArray("u_sampler", samplerSlots, m_rendererStorage.MaxTextureSlots);
        
        m_rendererStorage.m_vertices[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        m_rendererStorage.m_vertices[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        m_rendererStorage.m_vertices[2] = {0.5f, 0.5f, 0.0f, 1.0f};
        m_rendererStorage.m_vertices[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
    }

    void Renderer2D::Shutdown()
    {
    }

    void Renderer2D::BeginScene(OrthographicCamera& camera)
    {
        m_rendererStorage.m_textureShader->Bind();
        m_rendererStorage.m_textureShader->UploadUniformMat4("u_viewProjection", camera.GetViewProjectionMatrix());

        m_rendererStorage.m_quadIndexCount = 0;
        m_rendererStorage.m_quadVertexBufferPtr = m_rendererStorage.m_quadVertexBufferBase;

        m_rendererStorage.m_textureSlotIndexCount = 1;
    }

    void Renderer2D::EndScene()
    {
        const uint32_t dataSize = reinterpret_cast<uint8_t*>(m_rendererStorage.m_quadVertexBufferPtr) - reinterpret_cast
        <uint8_t*>(m_rendererStorage.m_quadVertexBufferBase);
        m_rendererStorage.m_vertexBuffer->SetData(m_rendererStorage.m_quadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        for (int i = 0; i < m_rendererStorage.m_textureSlotIndexCount; ++i)
        {
            m_rendererStorage.m_textures[i]->Bind(i);
        }

        RenderCommand::DrawIndexed(m_rendererStorage.m_vertexArray, m_rendererStorage.m_quadIndexCount);
    }

    void Renderer2D::DrawQuad(const SVector3& position, const SVector2& size, const SVector4& color)
    {
        DrawQuadTextured(position, size, m_rendererStorage.m_whiteTexture, color);
    }

    void Renderer2D::DrawRotatedQuad(const SVector3& position, const SVector2& size, float rotation,
                                     const SVector4& color)
    {
        DrawRotatedQuadTextured(position, size, rotation, m_rendererStorage.m_whiteTexture, {1.0f, 1.0f}, color);
    }

    void Renderer2D::DrawQuadTextured(const SVector3& position, const SVector2& size, const Ref<Texture2D> texture,
                                      const SVector4& color, const SVector2& tilingSize)
    {
        float textureSlot = -1.0f;
        for (int i = 0; i < m_rendererStorage.m_textureSlotIndexCount; ++i)
        {
            if (*m_rendererStorage.m_textures[i].get() == *texture.get())
            {
                textureSlot = static_cast<float>(i);
                break;
            }
        }

        if(textureSlot < 0.0f)
        {
            m_rendererStorage.m_textures[m_rendererStorage.m_textureSlotIndexCount] = texture;
            textureSlot = m_rendererStorage.m_textureSlotIndexCount;
            m_rendererStorage.m_textureSlotIndexCount++;
        }

        const SMat4 transform = SMath::Translate(SMat4(1.0f), position)
        * SMath::Scale(SMat4(1.0f), {size.x, size.y, 1.0f});

        m_rendererStorage.m_quadVertexBufferPtr->m_position = transform * m_rendererStorage.m_vertices[0];
        m_rendererStorage.m_quadVertexBufferPtr->m_color = color;
        m_rendererStorage.m_quadVertexBufferPtr->m_texCoord = SVector2(0.0f, 0.0f);
        m_rendererStorage.m_quadVertexBufferPtr->m_textureSlot = textureSlot;
        m_rendererStorage.m_quadVertexBufferPtr++;

        m_rendererStorage.m_quadVertexBufferPtr->m_position = transform * m_rendererStorage.m_vertices[1];
        m_rendererStorage.m_quadVertexBufferPtr->m_color = color;
        m_rendererStorage.m_quadVertexBufferPtr->m_texCoord = SVector2(1.0f, 0.0f);
        m_rendererStorage.m_quadVertexBufferPtr->m_textureSlot = textureSlot;
        m_rendererStorage.m_quadVertexBufferPtr++;

        m_rendererStorage.m_quadVertexBufferPtr->m_position = transform * m_rendererStorage.m_vertices[2];
        m_rendererStorage.m_quadVertexBufferPtr->m_color = color;
        m_rendererStorage.m_quadVertexBufferPtr->m_texCoord = SVector2(1.0f, 1.0f);
        m_rendererStorage.m_quadVertexBufferPtr->m_textureSlot = textureSlot;
        m_rendererStorage.m_quadVertexBufferPtr++;

        m_rendererStorage.m_quadVertexBufferPtr->m_position = transform * m_rendererStorage.m_vertices[3];
        m_rendererStorage.m_quadVertexBufferPtr->m_color = color;
        m_rendererStorage.m_quadVertexBufferPtr->m_texCoord = SVector2(0.0f, 1.0f);
        m_rendererStorage.m_quadVertexBufferPtr->m_textureSlot = textureSlot;
        m_rendererStorage.m_quadVertexBufferPtr++;

        m_rendererStorage.m_quadIndexCount += 6;
    }

    void Renderer2D::DrawRotatedQuadTextured(const SVector3& position, const SVector2& size, float rotation,
                                             const Ref<Texture2D> texture, const SVector2& tilingSize,
                                             const SVector4& color)
    {
        float textureSlot = -1.0f;
        for (int i = 0; i < m_rendererStorage.m_textureSlotIndexCount; ++i)
        {
            if (*m_rendererStorage.m_textures[i].get() == *texture.get())
            {
                textureSlot = static_cast<float>(i);
                break;
            }
        }

        if (textureSlot < 0.0f)
        {
            m_rendererStorage.m_textures[m_rendererStorage.m_textureSlotIndexCount] = texture;
            textureSlot = m_rendererStorage.m_textureSlotIndexCount;
            m_rendererStorage.m_textureSlotIndexCount++;
        }

        const SMat4 transform = SMath::Translate(SMat4(1.0f), position)
            * SMath::Rotate(SMat4(1.0f), rotation, SVector3(0.0f, 0.0f, 1.0f))
            * SMath::Scale(SMat4(1.0f), {size.x, size.y, 1.0f});

        m_rendererStorage.m_quadVertexBufferPtr->m_position = transform * m_rendererStorage.m_vertices[0];
        m_rendererStorage.m_quadVertexBufferPtr->m_color = color;
        m_rendererStorage.m_quadVertexBufferPtr->m_texCoord = SVector2(0.0f, 0.0f);
        m_rendererStorage.m_quadVertexBufferPtr->m_textureSlot = textureSlot;
        m_rendererStorage.m_quadVertexBufferPtr++;

        m_rendererStorage.m_quadVertexBufferPtr->m_position = transform * m_rendererStorage.m_vertices[1];
        m_rendererStorage.m_quadVertexBufferPtr->m_color = color;
        m_rendererStorage.m_quadVertexBufferPtr->m_texCoord = SVector2(1.0f, 0.0f);
        m_rendererStorage.m_quadVertexBufferPtr->m_textureSlot = textureSlot;
        m_rendererStorage.m_quadVertexBufferPtr++;

        m_rendererStorage.m_quadVertexBufferPtr->m_position = transform * m_rendererStorage.m_vertices[2];
        m_rendererStorage.m_quadVertexBufferPtr->m_color = color;
        m_rendererStorage.m_quadVertexBufferPtr->m_texCoord = SVector2(1.0f, 1.0f);
        m_rendererStorage.m_quadVertexBufferPtr->m_textureSlot = textureSlot;
        m_rendererStorage.m_quadVertexBufferPtr++;

        m_rendererStorage.m_quadVertexBufferPtr->m_position = transform * m_rendererStorage.m_vertices[3];
        m_rendererStorage.m_quadVertexBufferPtr->m_color = color;
        m_rendererStorage.m_quadVertexBufferPtr->m_texCoord = SVector2(0.0f, 1.0f);
        m_rendererStorage.m_quadVertexBufferPtr->m_textureSlot = textureSlot;
        m_rendererStorage.m_quadVertexBufferPtr++;

        m_rendererStorage.m_quadIndexCount += 6;
    }
}

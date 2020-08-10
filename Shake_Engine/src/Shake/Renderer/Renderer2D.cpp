#include "sepch.h"
#include "Renderer2D.h"


#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Camera/OrthographicCamera.h"

namespace Shake
{
    Renderer2DStorage* Renderer2D::m_rendererStorage = new Renderer2DStorage(); 
    
    void Renderer2D::Initialize()
    {
        m_rendererStorage->m_vertexArray.reset(Shake::VertexArray::Create());

        float vertices_01[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };
        unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Shake::VertexBuffer::Create(vertices_01, sizeof(vertices_01)));
        const Shake::BufferLayout layout = {
            {"a_position", Shake::ShaderDataType::Float3},
            {"a_texcoord", Shake::ShaderDataType::Float2}
        };
        vertexBuffer->SetLayout(layout);
        m_rendererStorage->m_vertexArray->AddVertexBuffer(vertexBuffer);

        Ref<IndexBuffer> indexBuffer;
        indexBuffer.reset(Shake::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_rendererStorage->m_vertexArray->SetIndexBuffer(indexBuffer);

        m_rendererStorage->m_textureShader = Shader::Create("Content/Shaders/Texture.glsl");

        m_rendererStorage->m_whiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        m_rendererStorage->m_whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    }

    void Renderer2D::Shutdown()
    {
        delete m_rendererStorage;
        m_rendererStorage = nullptr;
    }

    void Renderer2D::BeginScene(OrthographicCamera& camera)
    {
         m_rendererStorage->m_textureShader->Bind();
         m_rendererStorage->m_textureShader->UploadUniformMat4("u_viewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
    
    }

    void Renderer2D::DrawQuad(const SVector3& position, const SVector2& size, const SVector4& color)
    {
        DrawQuadTextured(position, size, m_rendererStorage->m_whiteTexture, color);
    }

    void Renderer2D::DrawQuadTextured(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, const SVector4& color, const SVector2& tilingSize)
    {
        SMat4 transform = SMath::Translate(SMat4(1.0f), position);
        transform = SMath::Scale(transform, SVector3(size.x, size.y, 1.0f));

        m_rendererStorage->m_textureShader->Bind();
        m_rendererStorage->m_textureShader->UploadUniformMat4("u_Transform", transform);
        m_rendererStorage->m_textureShader->UploadUniformFloat4("u_color", color);
        m_rendererStorage->m_textureShader->UploadUniformFloat2("u_tilingSize", tilingSize);
        m_rendererStorage->m_textureShader->UploadUniformInt("u_sampler",0);

        texture->Bind();
        
        m_rendererStorage->m_vertexArray->Bind(); 
        RenderCommand::DrawIndexed(m_rendererStorage->m_vertexArray);
    }
}

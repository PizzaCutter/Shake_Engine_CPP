#include "sepch.h"
#include "BaseLayer.h"

#include "Shake/Core/Timestep.h"

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"


BaseLayer::BaseLayer() : Layer("Base"),
                         m_orthoCameraController(1280.0f / 720.0f),
                         m_playerPosition(0.0f),
                         m_editableColor(SVector3(1.0f))
{
    m_vertexArray.reset(Shake::VertexArray::Create());

    // Index buffer
    float vertices_01[4 * 5] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };
    unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

    Shake::Ref<Shake::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(Shake::VertexBuffer::Create(vertices_01, sizeof(vertices_01)));
    const Shake::BufferLayout layout = {
        {"a_position", Shake::ShaderDataType::Float3},
        {"a_texcoord", Shake::ShaderDataType::Float2}
    };
    vertexBuffer->SetLayout(layout);
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    Shake::Ref<Shake::IndexBuffer> indexBuffer;
    indexBuffer.reset(Shake::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_vertexArray->SetIndexBuffer(indexBuffer);

    m_shaderLibrary.Load("Content/Shaders/Texture.glsl");

    m_Texture = Shake::Texture2D::Create("Content/Textures/grid.png");
    m_TransparentTexture = Shake::Texture2D::Create("Content/Textures/Test.png");
}

BaseLayer::~BaseLayer()
{
}

void BaseLayer::OnAttach()
{
}

void BaseLayer::OnDetach()
{
}

auto BaseLayer::OnUpdate(Shake::Timestep timeStep) -> void
{
    if (Shake::Input::IsKeyPressed(Shake::KeyCode::L))
    {
        m_playerPosition.x += m_playerMovementSpeed * timeStep.GetSeconds();
    }
    if (Shake::Input::IsKeyPressed(Shake::KeyCode::J))
    {
        m_playerPosition.x -= m_playerMovementSpeed * timeStep.GetSeconds();
    }
    if (Shake::Input::IsKeyPressed(Shake::KeyCode::I))
    {
        m_playerPosition.y += m_playerMovementSpeed * timeStep.GetSeconds();
    }
    if (Shake::Input::IsKeyPressed(Shake::KeyCode::K))
    {
        m_playerPosition.y -= m_playerMovementSpeed * timeStep.GetSeconds();
    }

    m_orthoCameraController.OnUpdate(timeStep); 

    Shake::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Shake::RenderCommand::Clear();

    Shake::Renderer::BeginScene(m_orthoCameraController.GetCamera());

    Shake::Ref<Shake::Shader> shader = m_shaderLibrary.Get("Texture");
    shader->UploadUniformFloat3("u_color", m_editableColor);
    shader->UploadUniformInt("u_sampler", 0);

    SMat4 transform = SMath::Translate(SMat4(1.0f), m_playerPosition);
    transform = SMath::Scale(transform, SVector3(0.5f));

    m_Texture->Bind();

    int gridSize = 10;
    float tileOffset = 0.15f;
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            SVector3 tilePosition = SVector3(i * tileOffset, j * tileOffset, 0.0f);
            SMat4 tempTransform = SMath::Translate(SMat4(1.0f), tilePosition);
            tempTransform = SMath::Scale(tempTransform, SVector3(0.1f));

            Shake::Renderer::Submit(m_vertexArray, shader, tempTransform);
        }
    }

    m_TransparentTexture->Bind();
    Shake::Renderer::Submit(m_vertexArray, shader, transform);

    Shake::Renderer::EndScene();
}

void BaseLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_editableColor));

    ImGui::End();
}

void BaseLayer::OnEvent(Shake::Event& event)
{
    m_orthoCameraController.OnEvent(event);
}

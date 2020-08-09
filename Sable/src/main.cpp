#include <iostream>
#include "Shake.h"

#include "imgui/imgui.h"

#include "glm/gtc/type_ptr.hpp"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "Shake/Renderer/Texture.h"

#include "Shake/Math/SMath.h"

namespace Shake {
    class Texture2D;
}

class BaseLayer : public Shake::Layer
{
public:
    BaseLayer() : Layer("Base"),
                  m_orthoCamera(-1.6f, 1.6f, -0.9f, 0.9f),
                  m_playerPosition(0.0f),
                  m_editableColor(SVector3(1.0f)) 
    {
        Shake::RenderCommand::Initialize();
        
        m_vertexArray.reset(Shake::VertexArray::Create());

        // Index buffer
        float vertices_01[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 
            0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 
            -0.5f, 0.5f, 0.0f,  0.0f, 1.0f
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
       
        m_Shader.reset(Shake::Shader::Create("Content/Shaders/Texture.glsl"));        

        m_Texture = Shake::Texture2D::Create("Content/Textures/grid.png");
        m_TransparentTexture = Shake::Texture2D::Create("Content/Textures/Test.png");
    }

    void OnUpdate(Shake::Timestep timestep) override
    {
        const float cameraMovementSpeed = 5.0f;

        if (Shake::Input::IsKeyPressed(Shake::KeyCode::W))
        {
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(0.0f, cameraMovementSpeed, 0.0f) * timestep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Shake::Input::IsKeyPressed(Shake::KeyCode::S))
        {
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(0.0f, -cameraMovementSpeed, 0.0f) * timestep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Shake::Input::IsKeyPressed(Shake::KeyCode::A))
        {
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(-cameraMovementSpeed, 0.0f, 0.0f) * timestep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Shake::Input::IsKeyPressed(Shake::KeyCode::D))
        {
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(cameraMovementSpeed, 0.0f, 0.0f) * timestep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }

        if(Shake::Input::IsKeyPressed(Shake::KeyCode::L))
        {
            m_playerPosition.x += cameraMovementSpeed * timestep.GetSeconds();
        }
        if(Shake::Input::IsKeyPressed(Shake::KeyCode::J))
        {
            m_playerPosition.x -= cameraMovementSpeed * timestep.GetSeconds();
        }
        if(Shake::Input::IsKeyPressed(Shake::KeyCode::I))
        {
            m_playerPosition.y += cameraMovementSpeed * timestep.GetSeconds();
        }
        if(Shake::Input::IsKeyPressed(Shake::KeyCode::K))
        {
            m_playerPosition.y -= cameraMovementSpeed * timestep.GetSeconds();
        }

        Shake::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Shake::RenderCommand::Clear();

        Shake::Renderer::BeginScene(m_orthoCamera);
       
        m_Shader->UploadUniformFloat3("u_color", m_editableColor);
        m_Shader->UploadUniformInt("u_sampler", 0);
        
        SMat4 transform = SMath::Translate(SMat4(1.0f), m_playerPosition);
        transform = SMath::Scale(transform, SVector3(0.5f));

        
        m_Texture->Bind();
        //Shake::Renderer::Submit(m_vertexArray, m_Shader, transform);

        int gridSize = 10;
        float tileOffset = 0.15f;
        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                SVector3 tilePosition = SVector3(i * tileOffset, j * tileOffset, 0.0f);
                SMat4 tempTransform = SMath::Translate(SMat4(1.0f), tilePosition);
                tempTransform = SMath::Scale(tempTransform, SVector3(0.1f));
                   
                Shake::Renderer::Submit(m_vertexArray, m_Shader, tempTransform);
            } 
        }
        
        m_TransparentTexture->Bind();
        Shake::Renderer::Submit(m_vertexArray, m_Shader, transform);

        Shake::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");

        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_editableColor));
        
        ImGui::End();
    }

    void OnEvent(Shake::Event& event) override
    {
        
    }

private:
    Shake::OrthographicCamera m_orthoCamera;

    Shake::Ref<Shake::Shader> m_Shader;
    Shake::Ref<Shake::Texture2D> m_Texture;
    Shake::Ref<Shake::Texture2D> m_TransparentTexture;
    Shake::Ref<Shake::VertexArray> m_vertexArray;

    SVector3 m_playerPosition;
    SVector3 m_editableColor;
};

class Sable : public Shake::Application
{
public:
    Sable(const std::string& applicationName) : Application(applicationName)
    {
        PushLayer(new BaseLayer());
    }

    ~Sable()
    {
    }
};

Shake::Application* Shake::CreateApplication()
{
    return new Sable("Sable");
}

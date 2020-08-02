#include <iostream>
#include "Shake.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"


class BaseLayer : public Shake::Layer
{
public:
    BaseLayer() : Layer("Base"),
                  m_orthoCamera(-1.6f, 1.6f, -0.9f, 0.9f),
                  m_trianglePosition(0.0f),
                  m_editableColor(glm::vec3(1.0f)) 
    {
        m_vertexArray.reset(Shake::VertexArray::Create());

        // Index buffer
        float vertices_01[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };
        unsigned int indices[3] = {0, 1, 2};

        Shake::Ref<Shake::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Shake::VertexBuffer::Create(vertices_01, sizeof(vertices_01)));
        const Shake::BufferLayout layout = {
            {"a_position", Shake::ShaderDataType::Float3}
        };
        vertexBuffer->SetLayout(layout);
        m_vertexArray->AddVertexBuffer(vertexBuffer);

        Shake::Ref<Shake::IndexBuffer> indexBuffer;
        indexBuffer.reset(Shake::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_vertexArray->SetIndexBuffer(indexBuffer);

        // SECOND OBJECT
        float vertices_02[3 * 3] = {
            0.0f, -0.5f, 0.0f,
            1.0f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f
        };

        m_squareVertexArray.reset(Shake::VertexArray::Create());
        vertexBuffer.reset(Shake::VertexBuffer::Create(vertices_02, sizeof(vertices_02)));
        const Shake::BufferLayout layout_02 =
        {
            {"a_position", Shake::ShaderDataType::Float3}
        };
        vertexBuffer->SetLayout(layout_02);
        m_squareVertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices_02[3] = {0, 1, 2};
        indexBuffer.reset(Shake::IndexBuffer::Create(indices_02, sizeof(indices) / sizeof(uint32_t)));
        m_squareVertexArray->SetIndexBuffer(indexBuffer);

        m_Shader.reset(Shake::Shader::Create("Default.vs", "Default.fs"));
    }

    void OnUpdate(Shake::Timestep timestep) override
    {
        const float cameraMovementSpeed = 5.0f;

        if (Shake::Input::IsKeyPressed(Shake::KeyCode::W))
        {
            glm::vec3 pos = m_orthoCamera.GetPosition();
            pos += glm::vec3(0.0f, cameraMovementSpeed, 0.0f) * timestep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Shake::Input::IsKeyPressed(Shake::KeyCode::S))
        {
            glm::vec3 pos = m_orthoCamera.GetPosition();
            pos += glm::vec3(0.0f, -cameraMovementSpeed, 0.0f) * timestep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Shake::Input::IsKeyPressed(Shake::KeyCode::A))
        {
            glm::vec3 pos = m_orthoCamera.GetPosition();
            pos += glm::vec3(-cameraMovementSpeed, 0.0f, 0.0f) * timestep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Shake::Input::IsKeyPressed(Shake::KeyCode::D))
        {
            glm::vec3 pos = m_orthoCamera.GetPosition();
            pos += glm::vec3(cameraMovementSpeed, 0.0f, 0.0f) * timestep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }

        if(Shake::Input::IsKeyPressed(Shake::KeyCode::L))
        {
            m_trianglePosition.x += cameraMovementSpeed * timestep.GetSeconds();
        }
        if(Shake::Input::IsKeyPressed(Shake::KeyCode::J))
        {
            m_trianglePosition.x -= cameraMovementSpeed * timestep.GetSeconds();
        }
        if(Shake::Input::IsKeyPressed(Shake::KeyCode::I))
        {
            m_trianglePosition.y += cameraMovementSpeed * timestep.GetSeconds();
        }
        if(Shake::Input::IsKeyPressed(Shake::KeyCode::K))
        {
            m_trianglePosition.y -= cameraMovementSpeed * timestep.GetSeconds();
        }

        Shake::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Shake::RenderCommand::Clear();

        Shake::Renderer::BeginScene(m_orthoCamera);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_trianglePosition);
        transform = glm::scale(transform, glm::vec3(0.1f));
        std::dynamic_pointer_cast<Shake::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_color", m_editableColor);
        
        Shake::Renderer::Submit(m_vertexArray, m_Shader, transform);
        Shake::Renderer::Submit(m_squareVertexArray, m_Shader);

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
    Shake::Ref<Shake::VertexArray> m_vertexArray;
    Shake::Ref<Shake::VertexArray> m_squareVertexArray;

    glm::vec3 m_trianglePosition;
    glm::vec3 m_editableColor;
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

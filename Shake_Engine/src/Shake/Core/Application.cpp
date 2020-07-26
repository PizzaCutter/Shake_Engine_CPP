#include "sepch.h"
#include "Application.h"

#include "glad/glad.h"
#include <GL/gl.h>

#include "Log.h"
#include "Shake/Renderer/Buffer.h"


namespace Shake
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;


    Application::Application(const std::string& applicationName)
    {
        //SE_CORE_ASSERT(s_Instance != nullptr, "Application already exists");
        s_Instance = this;
        
        ApplicationName = applicationName;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_imGuiLayer = new ImGuiLayer();
        PushOverlay(m_imGuiLayer);

        m_VertexArray.reset(VertexArray::Create());
        
        // Index buffer
        float vertices_01 [3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };
        unsigned int indices [3] = { 0, 1, 2 };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices_01, sizeof(vertices_01)));
        const BufferLayout layout = {
            { "a_position", ShaderDataType::Float3 }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // SECOND OBJECT
        float vertices_02 [3 * 3] = {
            0.0f, -0.5f, 0.0f,
            1.0f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f
        };
         
        m_squareVertexArray.reset(VertexArray::Create());
        vertexBuffer.reset(VertexBuffer::Create(vertices_02, sizeof(vertices_02)));
        const BufferLayout layout_02 =
        {
            { "a_position", ShaderDataType::Float3}
        };
        vertexBuffer->SetLayout(layout_02);
        m_squareVertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices_02[3] = { 0, 1, 2 };
        indexBuffer.reset(IndexBuffer::Create(indices_02, sizeof(indices) / sizeof(uint32_t))); 
        m_squareVertexArray->SetIndexBuffer(indexBuffer); 

        m_Shader.reset(new Shader("Default.vs", "Default.fs")); 
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

        for(Layer* layer : m_LayerStack)
        {
            layer->OnEvent(event);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run()
    {
        while (m_running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            m_squareVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_squareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            m_Shader->Bind();
            m_VertexArray->Bind();
            
            glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            
            for(Layer* layer : m_LayerStack)
            {
               layer->OnUpdate(); 
            }
            
            m_imGuiLayer->Begin();
            for(Layer* layer : m_LayerStack)
            {
                m_imGuiLayer->OnImGuiRender();
            }
            m_imGuiLayer->End();
            
            m_Window->OnUpdate();
        }
        Shutdown();
    }

    void Application::Shutdown()
    {
    }

    bool Application::OnWindowClosed(WindowCloseEvent& event)
    {
        m_running = false;
        return true;
    }
}

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

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch(type)
        {
        case ShaderDataType::None: return GL_FLOAT;
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3: return GL_FLOAT;
        case ShaderDataType::Mat4: return GL_FLOAT;
        case ShaderDataType::Int: return GL_INT;
        case ShaderDataType::Int2: return GL_INT;
        case ShaderDataType::Int3: return GL_INT;
        case ShaderDataType::Int4: return GL_INT;
        case ShaderDataType::Bool: return GL_BOOL;
        default: ;
        }

        // TODO[rsmekens]: add dev exception
        return 0;
    }

    Application::Application(const std::string& applicationName)
    {
        //SE_CORE_ASSERT(s_Instance != nullptr, "Application already exists");
        s_Instance = this;
        
        ApplicationName = applicationName;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_imGuiLayer = new ImGuiLayer();
        PushOverlay(m_imGuiLayer);

        // Vertex array
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);
        
        // Index buffer
        float vertices [3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };
        
        unsigned int indices [3] = { 0, 1, 2 };
        
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->Bind();

        {
            BufferLayout layout = {
                { "a_position", ShaderDataType::Float3 }
            };
            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetBufferLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.m_type),
                                  element.m_normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  reinterpret_cast<const void*>(element.m_offset));
            index++;
        }

        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_IndexBuffer->Bind();

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
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
            
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

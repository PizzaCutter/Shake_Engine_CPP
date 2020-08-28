#include "sepch.h"
#include "Application.h"

#include "Log.h"
#include "GLFW/glfw3.h"
#include "Shake/Renderer/RenderCommand.h"


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

        RenderCommand::Initialize();
        
        m_imGuiLayer = new ImGuiLayer();
        PushOverlay(m_imGuiLayer);
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResizeCallback));

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
            const float time = static_cast<float>(glfwGetTime()); 
            const Timestep timestep = time - m_lastFrameTime;
            m_lastFrameTime = static_cast<float>(glfwGetTime());

            for(Layer* layer : m_LayerStack)
            {
               layer->OnUpdate(timestep);
            }

            m_imGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
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

    bool Application::OnWindowResizeCallback(WindowResizeEvent& event)
    {
        if(event.GetWidth() == 0 && event.GetHeight() == 0)
        {
            m_minimized = true;
            return false; 
        }
        
        m_minimized = false;
        RenderCommand::WindowResize(event.GetWidth(), event.GetHeight());
        
        return false;
    }
}

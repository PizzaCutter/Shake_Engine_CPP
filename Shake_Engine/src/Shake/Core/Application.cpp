#include "sepch.h"
#include "Application.h"

#include "Log.h"
#include "GLFW/glfw3.h"


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
            const float time = static_cast<float>(glfwGetTime()); 
            const Timestep timestep = time - m_lastFrameTime;
            m_lastFrameTime = static_cast<float>(glfwGetTime());

            for(Layer* layer : m_LayerStack)
            {
               layer->OnUpdate(timestep); 
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

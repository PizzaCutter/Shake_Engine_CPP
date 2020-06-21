#include "sepch.h"
#include "Application.h"

#include <GL/gl.h>

#include "Log.h"

namespace Shake
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application::Application(const std::string& applicationName)
    {
        ApplicationName = applicationName;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::OnEvent(Event& event)
    {
        SE_CORE_INFO("{0}", event.ToString());

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
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
            glClearColor(1, 0.5, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for(Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }
            
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

#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Shake/Window.h"
#include "Shake/Events/ApplicationEvent.h"

namespace Shake 
{

    class SHAKE_API Application
    {
    public:
        Application(const std::string& applicationName);
        virtual ~Application();
        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        void Run();
        void Shutdown();
    private:
        bool OnWindowClosed(WindowCloseEvent& event);
        
        std::string ApplicationName = "";
        std::unique_ptr<Window> m_Window;
        bool m_running = true;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
}

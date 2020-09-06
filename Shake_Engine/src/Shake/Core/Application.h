#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Shake/Window.h"
#include "Shake/Events/ApplicationEvent.h"
#include "Shake/IMGUI/ImGuiLayer.h"

namespace Shake 
{

    class Application
    {
    public:
        Application(const std::string& applicationName);
        virtual ~Application();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        void Run();
        void Shutdown();

        static Application& Get() { return *s_Instance; } 
        inline Window& GetWindow() { return *m_Window; }

        ImGuiLayer* GetImGuiLayer() { return m_imGuiLayer; }

        void Close();

    private:
        bool OnWindowClosed(WindowCloseEvent& event);
        bool OnWindowResizeCallback(WindowResizeEvent& event);

        std::string ApplicationName = "";
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_imGuiLayer;
        bool m_running = true;
        bool m_minimized = false;
        LayerStack m_LayerStack;
        
        float m_lastFrameTime = 0.0f;
        
        static Application* s_Instance;
    };

    Application* CreateApplication();
}

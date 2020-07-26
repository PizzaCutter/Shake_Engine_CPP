#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Shake/Window.h"
#include "Shake/Events/ApplicationEvent.h"
#include "Shake/IMGUI/ImGuiLayer.h"
#include "Shake/Renderer/Buffer.h"
#include "Shake/Renderer/Shader.h"
#include "Shake/Renderer/VertexArray.h"

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

        static Application& Get() { return *s_Instance; } 
        inline Window& GetWindow() { return *m_Window; }

    private:
        bool OnWindowClosed(WindowCloseEvent& event);
        
        std::string ApplicationName = "";
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_imGuiLayer;
        bool m_running = true;
        LayerStack m_LayerStack;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_vertexArray;
       
        std::shared_ptr<VertexArray> m_squareVertexArray;
        
        static Application* s_Instance;
    };

    Application* CreateApplication();
}

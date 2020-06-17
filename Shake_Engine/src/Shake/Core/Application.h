#pragma once

#include <string>

#include "Core.h"
#include "Shake/Window.h"

namespace Shake 
{
    class SHAKE_API Application
    {
    public:
        Application(const std::string& applicationName);
        virtual ~Application();

        void Run();
    private:
        std::string ApplicationName = "";
        std::unique_ptr<Window> m_Window;
        bool m_running = true;
    };

    Application* CreateApplication();
}

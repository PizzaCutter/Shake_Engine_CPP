#include "sepch.h"
#include "Application.h"

#include <iostream>

#include "Log.h"

namespace Shake
{
    Application::Application(const std::string& applicationName)
    {
        ApplicationName = applicationName;
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_running)
        {
            m_Window->OnUpdate(); 
        }
    }
}

#include "sepch.h"
#include "Application.h"

#include <iostream>

#include "Log.h"

namespace Shake
{
    Application::Application(const std::string& applicationName)
    {
        ApplicationName = applicationName;
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (true)
        {
        
        }
    }
}

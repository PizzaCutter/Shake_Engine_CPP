#include "Application.h"

#include <iostream>

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
        std::cout << "Started Application " << ApplicationName << std::endl;
        while (true)
        {
    //        std::cout << "Running" << std::endl;
        }
    }
}

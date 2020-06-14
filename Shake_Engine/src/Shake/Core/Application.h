#pragma once

#include <string>

#include "Core.h"

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
    };

    Application* CreateApplication();
}
#pragma once
#include "Shake/Core/Application.h"

#ifdef SE_PLATFORM_WINDOWS
    extern Shake::Application* Shake::CreateApplication();

    int main(int argc, char** argv)
    {
        Shake::Log::Init();
        
        SE_CORE_WARN("Initialized Log System");
        SE_INFO("App Starting = {0}", 1);

        Shake::Application* app = Shake::CreateApplication();
        app->Run();
        delete app; 
    }
#else

#endif
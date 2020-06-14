#pragma once
#include "Shake/Core/Application.h"

#ifdef SE_PLATFORM_WINDOWS
    extern Shake::Application* Shake::CreateApplication();

    int main(int argc, char** argv)
    {
        auto app = Shake::CreateApplication();
        app->Run();
        delete app;
        return 0;
    }
#else

#endif
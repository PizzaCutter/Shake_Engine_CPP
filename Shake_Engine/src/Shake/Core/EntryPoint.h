#pragma once
#include "Shake/Core/Application.h"

#ifdef SE_PLATFORM_WINDOWS
    extern Shake::Application* Shake::CreateApplication();

    int main(int argc, char** argv)
    {
        Shake::Log::Init();
        
        SE_CORE_WARN("Initialized Log System");
        SE_INFO("App Starting = {0}", 1);
        
        SE_PROFILE_BEGIN_SESSION("Startup", "startup-profile.json");
        Shake::Application* app = Shake::CreateApplication();
        SE_PROFILE_END_SESSION();
        
        SE_PROFILE_BEGIN_SESSION("Update", "update-profile.json");       
        app->Run();
        SE_PROFILE_END_SESSION(); 

        SE_PROFILE_BEGIN_SESSION("Shutdown", "shutdown-profile.json");
        delete app;
        SE_PROFILE_END_SESSION();
    }
#else

#endif
#pragma once

#ifdef SE_PLATFORM_WINDOWS
    #ifdef SE_BUILD_DLL
        #define SHAKE_API __declspec(dllexport)
    #else
        #define SHAKE_API __declspec(dllimport)
    #endif
#else
    #error Shake only supports windows!
#endif

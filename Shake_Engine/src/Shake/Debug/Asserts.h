#pragma once

#ifdef SE_ENABLE_ASSERTS
    #define SE_ASSERT(x, ...) { if(!(x)) { SELOG(LogVerbosity::Error,"Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define SE_CORE_ASSERT(x, ...) { if(!(x)) { SE_ENGINE_LOG(LogVerbosity::Error,"Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define SE_ASSERT(x, ...)
    #define SE_CORE_ASSERT(x, ...)
#endif

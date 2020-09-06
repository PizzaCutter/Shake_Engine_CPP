#pragma once
#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Shake
{
    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define SE_CORE_TRACE(...) ::Shake::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SE_CORE_INFO(...) ::Shake::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SE_CORE_WARN(...) ::Shake::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SE_CORE_ERROR(...) ::Shake::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SE_CORE_FATAL(...) ::Shake::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define SE_TRACE(...) ::Shake::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SE_INFO(...) ::Shake::Log::GetClientLogger()->info(__VA_ARGS__)
#define SE_WARN(...) ::Shake::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SE_ERROR(...) ::Shake::Log::GetClientLogger()->error(__VA_ARGS__)
#define SE_FATAL(...) ::Shake::Log::GetClientLogger()->fatal(__VA_ARGS__)

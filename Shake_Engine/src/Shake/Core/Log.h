#pragma once

#include "spdlog/spdlog.h"

namespace Shake
{
    enum class LogVerbosity
    {
        Verbose,
        Info,
        Warning,
        Error
    };
    
    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

        template<typename... Args>
        inline static void LogEngineMessage(LogVerbosity verbosity, const std::string& context, const std::string& formatString, Args... args) 
        {
            const std::string totalString = context + " | " + formatString;

            switch(verbosity)
            {
            case LogVerbosity::Verbose:
                s_CoreLogger->trace(totalString, args...);
                return;
            case LogVerbosity::Info: 
                s_CoreLogger->info(totalString, args...);
                return;
            case LogVerbosity::Warning: 
                s_CoreLogger->warn(totalString, args...);
                return;
            case LogVerbosity::Error: 
                s_CoreLogger->error(totalString, args...); 
            }
        }
        
        template<typename... Args>
        inline static void LogMessage(LogVerbosity verbosity, const std::string& context, const std::string& formatString, Args... args) 
        {
            const std::string totalString = context + " | " + formatString;

            switch(verbosity)
            {
            case LogVerbosity::Verbose:
                s_ClientLogger->trace(totalString, args...);
                return;
            case LogVerbosity::Info: 
                s_ClientLogger->info(totalString, args...);
                return;
            case LogVerbosity::Warning: 
                s_ClientLogger->warn(totalString, args...);
                return;
            case LogVerbosity::Error: 
                s_ClientLogger->error(totalString, args...); 
            }
        }
        
        
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define JOYSTR_CUR_CLASS_FUNC (std::string(__FUNCTION__))

#define SE_ENGINE_LOG(LogVerbosity, FormatString, ...) ::Shake::Log::LogEngineMessage(LogVerbosity, JOYSTR_CUR_CLASS_FUNC, FormatString, __VA_ARGS__)
#define SELOG(LogVerbosity, FormatString, ...) ::Shake::Log::LogMessage(LogVerbosity, JOYSTR_CUR_CLASS_FUNC, FormatString, __VA_ARGS__)

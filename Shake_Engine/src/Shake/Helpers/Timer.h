#pragma once
#include <chrono>

namespace Shake
{
    template <typename Fn>
    class Timer
    {
    public:
        Timer(const char* name, Fn&& func)
            : m_name(name), m_stopped(false), m_func(func)
        {
            m_startTimePoint = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            if (m_stopped == false)
            {
                Stop();
            }
        }

        void Stop()
        {
            auto endTimePoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).
                              time_since_epoch().
                              count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().
                count();
            const float duration = (end - start) * 0.001f;
            
            m_func({m_name, duration});
            
            m_stopped = true;
        }

    private:
        const char* m_name;
        std::chrono::time_point<std::chrono::steady_clock> m_startTimePoint;
        bool m_stopped;
        Fn m_func;
    };
}

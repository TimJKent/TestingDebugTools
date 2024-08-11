#pragma once

#include <chrono>
#include <stdint.h>

namespace TDT
{
    class FPS_Profiler
    {
    public:
        FPS_Profiler();
        ~FPS_Profiler();
        static uint32_t GetFPS();
    private:
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    };
}
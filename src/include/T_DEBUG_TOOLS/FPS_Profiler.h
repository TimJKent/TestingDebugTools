#pragma once

#include <chrono>
#include <stdint.h>

#define TDT_PROFILER_PROFILE_SCOPE_FPS(...) TDT::FPS_Profiler var_profiler_fps_scoped;

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
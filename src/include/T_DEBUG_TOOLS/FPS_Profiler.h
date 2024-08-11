#pragma once

#include <chrono>
#include <stdint.h>

#define TDT_PROFILER_PROFILE_SCOPE_FPS(...) TDT_PROFILER_SCOPED_FPS(__PRETTY_FUNCTION__);
#define TDT_PROFILER_SCOPED_FPS(argument) TDT::FPS_Profiler var_fps_##argument("FPS");

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
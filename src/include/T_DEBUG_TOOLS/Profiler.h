#pragma once
#include <chrono>
#include <string>
#include "ProfilerCollector.h"
#include "TimebetweenProfilerCollector.h"

#define TDT_PROFILER_PROFILE_TIMEBETWEEN(expectedTime, tolerance)  TDT_PROFILER_TIMEBETWEEN(__PRETTY_FUNCTION__, expectedTime, tolerance);
#define TDT_PROFILER_TIMEBETWEEN(Argument, expectedTime, tolerance) TDT::Timebetween_Profiler var_##argument((__PRETTY_FUNCTION__), expectedTime, tolerance);
#define TDT_PROFILER_PRINT_TIMEBETWEEN(...) TimebetweenProfilerCollector::PrintProfilerData();

#define TDT_PROFILER_PROFILE_SCOPE(...)  TDT_PROFILER_SCOPED(__PRETTY_FUNCTION__);
#define TDT_PROFILER_SCOPED(argument) TDT::Scoped_Profiler var_##argument((__PRETTY_FUNCTION__));

#define TDT_PROFILER_PROFILE_SCOPE_FPS(...) TDT_PROFILER_SCOPED_FPS(__PRETTY_FUNCTION__);
#define TDT_PROFILER_SCOPED_FPS(argument) TDT::Scoped_Profiler var_fps_##argument("FPS");

namespace TDT
{
    inline double MicrosecondsToMilliseconds(double microseconds)
    {
        const double microToMilli = 0.001;
        return microseconds * microToMilli;
    }

    class Scoped_Profiler
    {
        public:
            Scoped_Profiler(const std::string& funcName)
            {
                functionName = funcName;
                startTime = std::chrono::high_resolution_clock::now();
                ProfilerCollector::PushFuncIDOntoCallStack(functionName);
            }
    
            ~Scoped_Profiler()
            {
                std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
                ProfilerCollector::AddProfilerFuncData(functionName, std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime));
            }
    
        private:
            std::string functionName;
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    };

    class Timebetween_Profiler
    {
        public:
            Timebetween_Profiler(const std::string& funcName, std::chrono::microseconds expectedTime, std::chrono::microseconds tolerancePlusOrMinus)
            {
                executedTime = std::chrono::high_resolution_clock::now();
                functionName = funcName;
                expected = expectedTime;
                tolerance = tolerancePlusOrMinus;
                TimebetweenProfilerCollector::AddProfilerFuncData(funcName,executedTime,  expectedTime, tolerancePlusOrMinus);
            }
    
            ~Timebetween_Profiler() = default;
            
        private:
            std::string functionName;
            std::chrono::microseconds expected;
            std::chrono::microseconds tolerance;
            std::chrono::time_point<std::chrono::high_resolution_clock> executedTime;
    };

}
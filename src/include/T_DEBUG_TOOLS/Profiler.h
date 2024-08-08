#pragma once
#include <chrono>
#include <string>
#include "ProfilerCollector.h"

#define TDT_PROFILER_PROFILE_SCOPE(...)  TDT_PROFILER_SCOPED(_PRETTY_FUNCTION__);
#define TDT_PROFILER_SCOPED(Argument) TDT::Scoped_Profiler var_##argument((__PRETTY_FUNCTION__));

namespace TDT
{
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
                double microsecondsEllapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                double millisecondsEllapsed = MicrosecondsToMilliseconds(microsecondsEllapsed);
                ProfilerCollector::AddProfilerFuncData(functionName, std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime));
            }
    
        private:
            inline double MicrosecondsToMilliseconds(double microseconds) const
            {
                const double microToMilli = 0.001;
                return microseconds * microToMilli;
            }

            std::string FormatFunctionRunTime(const std::string& functionName, double millisecondsEllapsed) const
            {
                return functionName + ": " + std::to_string(millisecondsEllapsed) + "ms";
            }

        private:
            std::string functionName;
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    };
}


#pragma once
#include <chrono>
#include <string>
#include <T_DEBUG_TOOLS/Logger/DebugLog.h>

#define TDT_PROFILER_PROFILE_SCOPE(...)  TDT_PROFILER_SCOPED(_PRETTY_FUNCTION__);
#define TDT_PROFILER_SCOPED(Argument) T_DEBUG_TOOLS::Scoped_Profiler var_##argument((__PRETTY_FUNCTION__));

namespace T_DEBUG_TOOLS
{
    class Scoped_Profiler
    {
        public:
            Scoped_Profiler(const std::string& funcName)
            {
                functionName = funcName;
                startTime = std::chrono::high_resolution_clock::now();
            }
    
            ~Scoped_Profiler()
            {
                std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
                double microsecondsEllapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                double millisecondsEllapsed = MicrosecondsToMilliseconds(microsecondsEllapsed);

                TDT_LOG(FormatFunctionRunTime(functionName, millisecondsEllapsed));
            }
    
        private:
            inline double MicrosecondsToMilliseconds(double microseconds)
            {
                const double microToMilli = 0.001;
                return microseconds * microToMilli;
            }

            std::string FormatFunctionRunTime(const std::string& functionName, double millisecondsEllapsed)
            {
                return functionName + ": " + std::to_string(millisecondsEllapsed) + "ms";
            }

        private:
            std::string functionName;
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    };
}


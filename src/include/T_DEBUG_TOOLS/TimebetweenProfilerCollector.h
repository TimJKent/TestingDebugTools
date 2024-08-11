#pragma once
#include <chrono>
#include <string>
#include "ProfilerCollector.h"

class TimebetweenProfilerFuncData 
{
public:
    std::string funcNameID;
    std::uint32_t timesCalledSoonerThanThreshold;
    std::uint32_t timesCalledWithinThreshold;
    std::uint32_t timesCalledLaterThanThreshold;

    std::chrono::microseconds fastestTimebetween;
    std::chrono::microseconds slowestTimebetween;

    std::chrono::time_point<std::chrono::high_resolution_clock> callTime;

    TimebetweenProfilerFuncData()
    {
        funcNameID = "";
        timesCalledSoonerThanThreshold = 0;
        timesCalledWithinThreshold = 0;
        timesCalledLaterThanThreshold = 0;

        fastestTimebetween =  std::chrono::microseconds::max();
        slowestTimebetween =  std::chrono::microseconds::min();
        callTime = std::chrono::high_resolution_clock::now();
    }

    TimebetweenProfilerFuncData(std::string funcName)
    {
        funcNameID = funcName;
        timesCalledSoonerThanThreshold = 0;
        timesCalledWithinThreshold = 0;
        timesCalledLaterThanThreshold = 0;

        fastestTimebetween =  std::chrono::microseconds::max();
        slowestTimebetween =  std::chrono::microseconds::min();
        callTime = std::chrono::high_resolution_clock::now();
    }

    static bool compare(TimebetweenProfilerFuncData& a, TimebetweenProfilerFuncData& b)
    {
        return (a.timesCalledWithinThreshold * a.timesCalledWithinThreshold) > (b.timesCalledWithinThreshold * b.timesCalledWithinThreshold);
    }
};


class TimebetweenProfilerCollector
{
    public:
        static void AddProfilerFuncData(const std::string& funcNameId, std::chrono::time_point<std::chrono::high_resolution_clock> funcStartTime, std::chrono::microseconds expectedTimeBetween, std::chrono::microseconds tolerance);
        static void PrintProfilerData();
        static void PushFuncIDOntoCallStack(const std::string& funcNameId);
    private:
        static inline double MicrosecondsToMilliseconds(double microseconds)
        {
            const double microToMilli = 0.001;
            return microseconds * microToMilli;
        }

        static inline std::string FormatFunctionRunTime(const std::string& functionName, uint32_t timesCalledSoonerThanThreshold,  uint32_t timesCalledLaterThanThreshold,  uint32_t timesCalledWithinThreshold,  double fastestTimebetween,  double slowestTimebetween)
        {
            std::string output = std::format(
                "| CTS:{1:<.5s} CTL:{2:.5s} COT:{3:.5s} FST:{4:.5s}ms SLW:{5:.5s}ms {0:>115}|", 
                functionName, 
                std::to_string(timesCalledSoonerThanThreshold), 
                std::to_string(timesCalledLaterThanThreshold), 
                std::to_string(timesCalledWithinThreshold),
                std::to_string(fastestTimebetween),
                std::to_string(slowestTimebetween)
            );
            return  output;
        }
        
    private:
        static std::map<std::string, TimebetweenProfilerFuncData> timedProfilerDataMap;
};
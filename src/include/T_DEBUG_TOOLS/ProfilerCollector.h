#pragma once

#define TDT_DEBUG_ENABLED 1
#define TDT_PRINT_WITH_STD_COUT 1


#include <string>
#include <cstdint>
#include <chrono>
#include <map>
#include <stack>
#include <format>


#define TDT_PROFILER_PRINT(...)  ProfilerCollector::PrintProfilerData();

class ProfilerFuncData 
{
public:
    std::string funcNameID;
    std::uint32_t funcCallCount;

    std::chrono::microseconds fastestRuntime;
    std::chrono::microseconds slowestRuntime;
    std::chrono::microseconds averageRuntime;

    ProfilerFuncData()
    {
        funcNameID = "";
        funcCallCount = 0;

        fastestRuntime =  std::chrono::microseconds::max();
        slowestRuntime =  std::chrono::microseconds::min();
        averageRuntime =  std::chrono::microseconds::zero();
    }

    ProfilerFuncData(std::string funcName)
    {
        funcNameID = funcName;
        funcCallCount = 0;

        fastestRuntime =  std::chrono::microseconds::max();
        slowestRuntime =  std::chrono::microseconds::min();
        averageRuntime =  std::chrono::microseconds::zero();
    }

   // ProfilerFuncData(ProfilerFuncData& copy)
   // {
   //     funcNameID = copy.funcNameID;
   //     funcCallCount = copy.funcCallCount;
//
   //     fastestRuntime = copy.fastestRuntime;
   //     slowestRuntime = copy.slowestRuntime;
   //     averageRuntime = copy.averageRuntime;
   // }

    static bool compare(ProfilerFuncData& a, ProfilerFuncData& b)
    {
        return (a.averageRuntime * a.funcCallCount) > (b.averageRuntime * b.funcCallCount);
    }
};


class ProfilerCollector
{
    public:
        static void AddProfilerFuncData(const std::string& funcNameId, std::chrono::microseconds runtime);
        static void PrintProfilerData();
        static void PushFuncIDOntoCallStack(const std::string& funcNameId);
    private:
        static  std::chrono::microseconds CalculateNewAverage(std::chrono::microseconds currentAverage, std::uint64_t funcCallCount, std::chrono::microseconds newTime);
        static inline double MicrosecondsToMilliseconds(double microseconds)
        {
            const double microToMilli = 0.001;
            return microseconds * microToMilli;
        }

        static inline std::string FormatFunctionRunTime(const std::string& functionName, double totalMillisecondsEllapsed,  double minMillisecondsEllapsed,  double averageMillisecondsEllapsed,  double maxMillisecondsEllapsed,  uint64_t callCount)
        {
            std::string output = std::format(
                "| Ttl:{1:<.5s}ms Min:{2:.5s}ms Avg:{3:.5s}ms Max:{4:.5s}ms Cnt:{5:10} {0:>94}|", 
                functionName, 
                std::to_string(totalMillisecondsEllapsed), 
                std::to_string(minMillisecondsEllapsed), 
                std::to_string(averageMillisecondsEllapsed),
                std::to_string(maxMillisecondsEllapsed),
                std::to_string(callCount)
            );
            return  output;
        }
        
    private:
        static std::map<std::string, ProfilerFuncData> profilerDataMap;
        static std::stack<std::string> profilerFuncIDStack;
};
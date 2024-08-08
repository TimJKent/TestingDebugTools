#define TDT_DEBUG_ENABLED 1
#define TDT_PRINT_WITH_STD_COUT 1

#include "include/T_DEBUG_TOOLS/Logger.h"
#include "include/T_DEBUG_TOOLS/ProfilerCollector.h"
#include <format>
#include <utility>


std::map<std::string, ProfilerFuncData> ProfilerCollector::profilerDataMap = {};
std::stack<std::string> ProfilerCollector::profilerFuncIDStack = {};

void ProfilerCollector::AddProfilerFuncData(const std::string& funcNameId, std::chrono::microseconds runtime) 
{   
    profilerFuncIDStack.pop();
    ProfilerFuncData profilerFuncData(funcNameId);

    if(profilerDataMap.count(funcNameId))
    {
        profilerFuncData = ProfilerFuncData(profilerDataMap[funcNameId]);
    }

    profilerFuncData.funcCallCount++;

    profilerFuncData.averageRuntime = CalculateNewAverage(profilerFuncData.averageRuntime, profilerFuncData.funcCallCount, runtime);

    if(runtime < profilerFuncData.fastestRuntime)
    {
        profilerFuncData.fastestRuntime = runtime;
    }

    if(runtime > profilerFuncData.slowestRuntime)
    {
        profilerFuncData.slowestRuntime = runtime;
    }

    profilerDataMap[funcNameId] = profilerFuncData;

    if(profilerFuncIDStack.empty())
    {
        PrintProfilerData();
    }
}

void ProfilerCollector::PushFuncIDOntoCallStack(const std::string& funcNameId)
{
    profilerFuncIDStack.push(funcNameId);
}


std::chrono::microseconds ProfilerCollector::CalculateNewAverage(std::chrono::microseconds currentAverage, std::uint64_t funcCallCount, std::chrono::microseconds newTime)
{
    int64_t funcTotalRunTimePS = currentAverage.count() * (funcCallCount - 1);
    
    std::chrono::microseconds newAverage((funcTotalRunTimePS + (int64_t)newTime.count())/funcCallCount);

    return newAverage;
}

void ProfilerCollector::PrintProfilerData()
{
    TDT_LOG(std::format("{:-^160}","PROFILER DATA"));

    std::vector<ProfilerFuncData> sortedData;
    
    for(auto& it : profilerDataMap)
    {
        sortedData.push_back(it.second);
    }

    sort(sortedData.begin(), sortedData.end(), ProfilerFuncData::compare);
 
    for(auto& sortedIterator : sortedData)
    {
        double runtimeAsMilliseconds = MicrosecondsToMilliseconds(sortedIterator.averageRuntime.count() * sortedIterator.funcCallCount);
        double minAsMilliseconds = MicrosecondsToMilliseconds(sortedIterator.fastestRuntime.count());
        double avgAsMilliseconds = MicrosecondsToMilliseconds(sortedIterator.averageRuntime.count());
        double maxAsMilliseconds = MicrosecondsToMilliseconds(sortedIterator.slowestRuntime.count());

        std::string output = FormatFunctionRunTime(sortedIterator.funcNameID, runtimeAsMilliseconds, minAsMilliseconds, avgAsMilliseconds, maxAsMilliseconds, sortedIterator.funcCallCount);
        TDT_LOG(output);
        TDT_LOG(std::format("{:-^160}",""));
    }    
}

#define TDT_DEBUG_ENABLED 1
#define TDT_PRINT_WITH_STD_COUT 1

#include "include/T_DEBUG_TOOLS/Logger.h"
#include "include/T_DEBUG_TOOLS/TimebetweenProfilerCollector.h"
#include <format>
#include <utility>


std::map<std::string, TimebetweenProfilerFuncData> TimebetweenProfilerCollector::timedProfilerDataMap = {};

void TimebetweenProfilerCollector::AddProfilerFuncData(const std::string& funcNameId, std::chrono::time_point<std::chrono::high_resolution_clock> funcStartTime, std::chrono::microseconds expectedTimeBetween, std::chrono::microseconds tolerance) 
{   
    TimebetweenProfilerFuncData timedProfilerFuncData(funcNameId);

    if(timedProfilerDataMap.count(funcNameId))
    {
        timedProfilerFuncData = timedProfilerDataMap[funcNameId];
        std::chrono::microseconds timeBetween = std::chrono::duration_cast<std::chrono::microseconds>(funcStartTime - timedProfilerDataMap[funcNameId].callTime);
        

        if(timeBetween > expectedTimeBetween + tolerance)
        {
            timedProfilerFuncData.timesCalledLaterThanThreshold++;
        }
        else if(timeBetween < expectedTimeBetween - tolerance)
        {
            timedProfilerFuncData.timesCalledSoonerThanThreshold++;
        }
        else
        {
            timedProfilerFuncData.timesCalledWithinThreshold++;
        }

        if(timeBetween < timedProfilerFuncData.fastestTimebetween)
        {
            timedProfilerFuncData.fastestTimebetween = timeBetween;
        }
        if(timeBetween > timedProfilerFuncData.slowestTimebetween)
        {
            timedProfilerFuncData.slowestTimebetween = timeBetween;
        }
    }

    timedProfilerFuncData.callTime = funcStartTime;


    timedProfilerDataMap[funcNameId] = timedProfilerFuncData;
}

void TimebetweenProfilerCollector::PrintProfilerData()
{
    TDT_LOG(std::format("{:-^160}","TIMEBETWEEN PROFILER DATA"));

    std::vector<TimebetweenProfilerFuncData> sortedData;
    
    for(auto& it : timedProfilerDataMap)
    {
        sortedData.push_back(it.second);
    }

    sort(sortedData.begin(), sortedData.end(), TimebetweenProfilerFuncData::compare);
 
    for(auto& sortedIterator : sortedData)
    {
        double fastestTimebetween = MicrosecondsToMilliseconds(sortedIterator.fastestTimebetween.count());
        double slowestTimebetween = MicrosecondsToMilliseconds(sortedIterator.slowestTimebetween.count());
        

        std::string output = FormatFunctionRunTime(
            sortedIterator.funcNameID, 
            sortedIterator.timesCalledSoonerThanThreshold,  
            sortedIterator.timesCalledLaterThanThreshold, 
            sortedIterator.timesCalledWithinThreshold, 
            fastestTimebetween, 
           slowestTimebetween
        );

        TDT_LOG(output);
        TDT_LOG(std::format("{:-^160}",""));
    }    
}

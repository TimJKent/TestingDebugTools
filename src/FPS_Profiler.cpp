#include <T_DEBUG_TOOLS/FPS_Profiler.h>
#include <queue>

namespace TDT
{

static std::queue<uint32_t> fpsQueue;

FPS_Profiler::FPS_Profiler()
{
    startTime = std::chrono::high_resolution_clock::now();
}

FPS_Profiler::~FPS_Profiler()
{
    std::chrono::milliseconds funcRuntimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime);
    fpsQueue.push((1.0 / funcRuntimeMs.count()) * 1000.0);
    if(fpsQueue.size() > 10)
    {
        fpsQueue.pop();
    }
}

uint32_t FPS_Profiler::GetFPS(){
    uint32_t fps = 0;
    std::queue<uint32_t> copy_queue = fpsQueue;
    int count = 0;
    while(!copy_queue.empty())
    {
        count ++;
        fps+= copy_queue.front();
        copy_queue.pop();
    }
    if(count == 0){return 0;}
    return fps/count;
}

}
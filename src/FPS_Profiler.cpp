#include <T_DEBUG_TOOLS/FPS_Profiler.h>

namespace TDT
{
    
static uint32_t fps = 0; 

FPS_Profiler::FPS_Profiler()
{
    startTime = std::chrono::high_resolution_clock::now();
}

FPS_Profiler::~FPS_Profiler()
{
    std::chrono::milliseconds funcRuntimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime);
    fps = (1.0 / funcRuntimeMs.count()) * 1000.0;
}

uint32_t FPS_Profiler::GetFPS(){
    return fps;
}

}
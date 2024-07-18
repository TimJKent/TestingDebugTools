#include <iostream>
#include <BoxFactory.h>
#include <T_DEBUG_TOOLS/Logger/DebugLog.h>
#include <T_DEBUG_TOOLS/Profiler/Profiler.h>

int main()
{
    TDT_PROFILER_PROFILE_SCOPE();
    BoxFactory factory("FactoryA");

    factory.ChangeState(0);
    factory.ChangeState(1);
    
    for(int i =0 ; i < 10; i++)
    {
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
        factory.Update();
    }

    //while(1)
    //{
    //    factory.Update();
    //}
}
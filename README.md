# TestingDebugTools
A simple tool for logging and profiling.

<details>
<summary>Logging </summary>


### Setup
```cpp
#define TDT_DEBUG_ENABLED 1
#define TDT_PRINT_WITH_STD_COUT 1
#include "T_DEBUG_TOOLS/Logger.h"

int main()
{
  TDT_LOG("Hello World");
  return 0;
}
```

## Usage

LOG
```cpp
TDT_LOG("Message");

(HH:MM:SS) LOG: Message
```
WARN
```cpp
TDT_WARN("Message") 

filename.ext:linenumber: WARNING
  | Message
```

ERROR
```cpp
TDT_ERROR("Message")

filename.ext:linenumber: ERROR
  | Message
```

ASSERTION
```cpp
TDT_ASSERT(false, "Message")

Assertion failed: (("Message"), false), file filename.extention, line linenumber
```
</details>

![Screenshot 2024-08-07 223658](https://github.com/user-attachments/assets/64202724-e444-4628-b29f-84ce63563dc2)


## Profiling
  
<details>
<summary> Function Runtime Profiling </summary>

To profile a function call TDT_PROFILER_PROFILE_SCOPE() at the beginning of the scope. Each call to TDT_PROFILER_PROFILE_SCOPE() pushes to the Proflier Collector Stack. When the last stack data is poped the Profiler Collector will print stats sorted by total runtime.

```cpp
void Func()
{
  TDT_PROFILER_PROFILE_SCOPE();
  //Rest of Func
}
```

Output
![Screenshot 2024-08-07 225615](https://github.com/user-attachments/assets/cffff850-2d83-4c90-b2e1-9be52e5517ac)
  - Ttl: Total function runtime in ms
  - Min: Shortest function runtime in ms
  - Avg: Average function runtime in ms
  - Max: Longest function runtime
  - Cnt: Time function was called

</details>

<details>
<summary> Function Timebetween Profiling </summary>

Useful for testing functions that need to be called at an exact rep rate.
  
```cpp
TDT_PROFILER_PROFILE_TIMEBETWEEN(expectedRuntime, tolerance);
```
  - expectedRuntime: how often this function is expected to run in microseconds
  - tolerance: how many microseconds tolerance is acceptable

  Example
  If a function is supposed to be called every 100 milliseconds with +- 10 milliseconds tolerance

```cpp
TDT_PROFILER_PROFILE_TIMEBETWEEN(std::chrono::microseconds(100000), std::chrono::microseconds(10000));
```

```cpp
#define TDT_DEBUG_ENABLED 1
#define TDT_PRINT_WITH_STD_COUT 1
#include "src/include/T_DEBUG_TOOLS/Logger.h"
#include "src/include/T_DEBUG_TOOLS/Profiler.h"

int callTimes = 0;

void Print()
{
  TDT_PROFILER_PROFILE_TIMEBETWEEN(std::chrono::microseconds(500), std::chrono::microseconds(10));
  TDT_LOG("Log Text");
  callTimes ++;
}

int main()
{
  std::chrono::time_point<std::chrono::high_resolution_clock> lastCallTime = std::chrono::high_resolution_clock::now();
  while(callTimes < 10)
  {
    if(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - lastCallTime) >= std::chrono::microseconds(500))
    {
      Print();
      lastCallTime = std::chrono::high_resolution_clock::now();
    }
  }


  TDT_PROFILER_PRINT_TIMEBETWEEN();
  return 0;
}
```

Output
![Screenshot 2024-08-10 191008](https://github.com/user-attachments/assets/113ec5c8-48db-47be-ac43-031b35365a12)


  - CTS: Count of timebetween being too short (Lower is better)
  - CTL: Count of timebetween being too long (Lower is better)
  - COT: Count of timbetween being on time (Higher is better)
  - FST: Fastest timebetween
  - SLW: Slowest timebetwen

</details>



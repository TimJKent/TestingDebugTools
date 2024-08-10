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


<details>
<summary> Profiling </summary>
  


To profile a function call TDT_PROFILER_PROFILE_SCOPE() at the beginning of the scope. Each call to TDT_PROFILER_PROFILE_SCOPE() pushes to the Proflier Collector Stack. When the last stack data is poped the Profiler Collector will print stats sorted by total runtime.

```cpp
void Func()
{
  TDT_PROFILER_PROFILE_SCOPE();
  //Rest of Func
}
```

Output
```txt
(HH:MM:SS) LOG: void Func(): 1000.000000ms
```
</details>

![Screenshot 2024-08-07 225615](https://github.com/user-attachments/assets/cffff850-2d83-4c90-b2e1-9be52e5517ac)

# TestingDebugTools
A simple header only set of tools for logging and profiling.


![Screenshot 2024-08-07 223658](https://github.com/user-attachments/assets/64202724-e444-4628-b29f-84ce63563dc2)

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
<details>
<summary> Profiling </summary>

To profile a function call TDT_PROFILER_PROFILE_SCOPE() at the beginning of the scope.

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
</summary>


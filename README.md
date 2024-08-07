# TestingDebugTools


# Logging

## Setup
```cpp
#define T_DEBUG_ENABLED 1
#define TDT_PRINT_WITH_STD_COUT 1
#include <T_DEBUG_TOOLS>

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

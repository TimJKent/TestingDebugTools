#pragma once

#ifdef TDT_DEBUG_ENABLED

    #ifdef TDT_PRINT_WITH_STD_COUT
        #include <iostream>
        #define TDT_DEBUG_PRINT(stringToPrint) std::cout << stringToPrint << std::endl;
    #endif


    #ifdef TDT_DEBUG_PRINT
        #include <cassert>

        #define TDT_LINE_FILE_OUTPUT std::string(__FILE__) + ":" + std::string(__LINE__) + ": "
        #define TDT_DEBUG_TAB  "\n    | "

        #define TDT_DEBUG_TIME " (" + std::string(__TIME__) + ")"

        #define TDT_DEBUG_LOG_MESSAGE "DEBUG_LOG: "
        #define TDT_DEBUG_WARN_MESSAGE "DEBUG_WARN"
        #define TDT_DEBUG_ERROR_MESSAGE "DEBUG_ERROR"
        #define TDT_DEBUG_ASSERT_MESSAGE "DEBUG_ASSERT"


        #define TDT_LOG(...)      TDT_DEBUG_PRINT(std::string(TDT_DEBUG_TIME) + std::string(TDT_DEBUG_LOG_MESSAGE)  + std::string(__VA_ARGS__)) 
        #define TDT_WARN(...)     std::cout << TDT_LINE_FILE_OUTPUT << TDT_DEBUG_WARN_MESSAGE << TDT_DEBUG_TAB << (__VA_ARGS__) << std::endl;
        #define TDT_ERROR(...)    std::cout << TDT_LINE_FILE_OUTPUT << TDT_DEBUG_ERROR_MESSAGE << TDT_DEBUG_TAB << (__VA_ARGS__) << std::endl;
        #define TDT_ASSERT(assertion, ...) assert(((__VA_ARGS__), assertion))
        #define TDT_BREAK(...) assert(false)
    #else
        #error TDT_DEBUG_PRINT not defined!
    #endif


#else
    #warning <DEBUG_LOG.h> included but not enabled. Either remove include or define TDT_DEBUG_ENABLED
#endif
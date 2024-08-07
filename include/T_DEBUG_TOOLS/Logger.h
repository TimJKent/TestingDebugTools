#pragma once

#ifdef TDT_DEBUG_ENABLED

    #ifdef TDT_PRINT_WITH_STD_COUT
        #include <iostream>
        #define TDT_DEBUG_PRINT(stringToPrint) std::cout << stringToPrint << std::endl;
    #endif


    #ifdef TDT_DEBUG_PRINT
        #include <cassert>
        #include <string>

        #define TDT_LINE_FILE_OUTPUT std::string(__FILE__) + ":" + std::to_string(__LINE__)  + ": "
        #define TDT_DEBUG_TAB  "\n    | "

        #define TDT_DEBUG_TIME " (" + std::string(__TIME__) + ")"

        #define TDT_DEBUG_LOG_MESSAGE "LOG: "
        #define TDT_DEBUG_WARN_MESSAGE "WARNING"
        #define TDT_DEBUG_ERROR_MESSAGE "ERROR"
        #define TDT_DEBUG_ASSERT_MESSAGE "ASSERT"

        #define TDT_LOG(...)      TDT_DEBUG_PRINT(TDT_DEBUG_TIME + TDT_DEBUG_LOG_MESSAGE  + (__VA_ARGS__)) 
        #define TDT_WARN(...)     TDT_DEBUG_PRINT(TDT_LINE_FILE_OUTPUT + TDT_DEBUG_WARN_MESSAGE + TDT_DEBUG_TAB + (__VA_ARGS__));
        #define TDT_ERROR(...)    TDT_DEBUG_PRINT(TDT_LINE_FILE_OUTPUT + TDT_DEBUG_ERROR_MESSAGE + TDT_DEBUG_TAB + (__VA_ARGS__));
        #define TDT_ASSERT(assertion, ...) assert(((__VA_ARGS__), assertion))
    #else
        #error TDT_DEBUG_PRINT not defined!
    #endif


#else
    #warning <T_DEBUG_TOOLS/Logger.h> included but not enabled. Either remove include or define TDT_DEBUG_ENABLED
#endif
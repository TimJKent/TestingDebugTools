#pragma once

#ifdef TDT_DEBUG_ENABLED

    #ifdef TDT_PRINT_WITH_STD_COUT
        #include <iostream>
        #define TDT_DEBUG_PRINT(stringToPrint) std::cout << stringToPrint << std::endl;
    #endif


    #ifdef TDT_DEBUG_PRINT
        #include <cassert>
        #include <string>

        #define TDT_LINE_FILE_OUTPUT "\033[93m"+std::string(__FILE__) + "\033[0m:\033[94m" + std::to_string(__LINE__)  + "\033[0m: "
        #define TDT_DEBUG_TAB  "\n    | "

        #define TDT_DEBUG_TIME "(" + std::string(__TIME__) + ") "

        #define TDT_DEBUG_LOG_MESSAGE "\033[32mLOG\033[0m: "
        #define TDT_DEBUG_WARN_MESSAGE "\033[33mWARNING\033[0m"
        #define TDT_DEBUG_ERROR_MESSAGE "\033[31mERROR\033[0m"
        #define TDT_DEBUG_ASSERT_MESSAGE "\033[31mASSERT\033[0m"

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
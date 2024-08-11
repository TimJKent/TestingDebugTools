cmake_minimum_required(VERSION 3.10)

project("TestingDebugTools"
    VERSION 1.0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
PRIVATE
    src/ProfilerCollector.cpp
    src/TimebetweenProfilerCollector.cpp
    src/FPS_Profiler.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${PROJECT_SOURCE_DIR}/src/include
)
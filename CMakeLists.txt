cmake_minimum_required(VERSION 3.16)
project(SandSlope LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Load external dependencies from the cmake/ folder
include(cmake/Dependencies.cmake)

# Generate Executable
add_executable(SandSlope main.cpp)

target_link_libraries(SandSlope PRIVATE glfw glm::glm)

if(MSVC)
    target_compile_options(SandSlope PRIVATE /W4)
else()
    target_compile_options(SandSlope PRIVATE -Wall -Wextra)
endif()

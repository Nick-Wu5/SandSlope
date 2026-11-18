cmake_minimum_required(VERSION 3.18)
project(SandSlope LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Homebrew dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)                  
find_package(glm REQUIRED)
find_package(libfreenect REQUIRED)
find_library(FREENECT_LIB      freenect      HINTS ${FREENECT_LIBRARY_DIRS} REQUIRED)
find_library(FREENECT_SYNC_LIB freenect_sync HINTS ${FREENECT_LIBRARY_DIRS} REQUIRED)

# Silence Apple's OpenGL deprecation warnings
if(APPLE)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
endif()

# Committed glad
add_library(glad STATIC external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(SandSlope main.cpp util.cpp)
target_include_directories(SandSlope PRIVATE ${FREENECT_INCLUDE_DIRS})
target_link_libraries(SandSlope PRIVATE
    OpenGL::GL glfw glm::glm glad
    ${FREENECT_LIB} ${FREENECT_SYNC_LIB})


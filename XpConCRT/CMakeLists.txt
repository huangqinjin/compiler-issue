cmake_minimum_required(VERSION 3.20)
project(XpConCRT)

# On Windows XP, ConCRT initialization during DLL loading causes Loader Deadlock
# To avoid this issue, delay loading the dll and initialize ConCRT in main().
option(DELAY "Delay Loading DLL" ON)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(CMakePrintHelpers)

cmake_print_variables(
    DELAY
    CMAKE_BUILD_TYPE
    CMAKE_GENERATOR
    CMAKE_CXX_COMPILER
    CMAKE_CXX_COMPILER_VERSION
    CMAKE_GENERATOR_PLATFORM
    CMAKE_VS_PLATFORM_NAME
    CMAKE_GENERATOR_TOOLSET
    CMAKE_VS_PLATFORM_TOOLSET
    CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE
    CMAKE_VS_PLATFORM_TOOLSET_VERSION
)

if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.20)
    message(WARNING "Visual Studio 2019 will not support Windows XP")
endif()

add_compile_options(/Zc:threadSafeInit-)
add_compile_definitions(_WIN32_WINNT=0x0501)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SUBSYSTEM_VERSION 5.02)
else()
    set(SUBSYSTEM_VERSION 5.01)
endif()

if(NOT CMAKE_VS_PLATFORM_TOOLSET)
    # "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64_x86 -vcvars_ver=14.16
    include_directories("C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Include")
    link_directories("C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib")
    add_compile_definitions(_USING_V110_SDK71_)
    add_link_options(/SUBSYSTEM:CONSOLE,${SUBSYSTEM_VERSION})
else()
    # Need to install the following Visual Studio 2019 Components
    #  1. C++ Windows XP Support for VS 2017 (v141) tools
    #  2. MSVC v141 - VS 2017 C++ x64/x86 build tools (v14.16)
    
    # cmake .. -Tv141_xp -AWin32
    # cmake --build . --config RelWithDebInfo
endif()


add_library(${PROJECT_NAME}Init SHARED init.cpp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Init)

if(DELAY)
    target_link_libraries(${PROJECT_NAME} PRIVATE delayimp)
    target_link_options(${PROJECT_NAME} PRIVATE /DELAYLOAD:$<TARGET_FILE_NAME:${PROJECT_NAME}Init>)
endif()

enable_testing()
add_test(NAME "Init ConCRT in DLL" COMMAND ${PROJECT_NAME} 0)
add_test(NAME "Init ConCRT in main" COMMAND ${PROJECT_NAME} 1)

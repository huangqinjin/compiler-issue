cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")
set(CMAKE_TOOLCHAIN_FILE $ENV{ANDROID_NDK_ROOT}/build/cmake/android.toolchain.cmake)
set(ANDROID_STL c++_shared)
set(ANDROID_NATIVE_API_LEVEL 24)
#set(ANDROID_LD lld)

set(ABI "" CACHE STRING "Android ABIs: arm, arm64, x86, x64")
set_property(CACHE ABI PROPERTY STRINGS arm arm64 x86 x64)

if(ABI STREQUAL arm)
    set(ANDROID_ABI armeabi-v7a)
elseif(ABI STREQUAL arm64)
    set(ANDROID_ABI arm64-v8a)
elseif(ABI STREQUAL x86)
    set(ANDROID_ABI x86)
elseif(ABI STREQUAL x64)
    set(ANDROID_ABI x86_64)
elseif(ABI)
    message(FATAL_ERROR "Not supported ABI: ${ABI}")
endif()

# arm64-v8a is default to bfd which is very buggy.
# May never get gold as default because in favor of lld.
# https://github.com/android/ndk/issues/556
# https://github.com/android/ndk/issues/1183
# https://github.com/opencv/opencv/issues/17282
set(LD "" CACHE STRING "Pass to -fuse-ld=, options are bfd, gold, lld.")
set_property(CACHE LD PROPERTY STRINGS bfd gold lld)

set(ANDROID_LINKER_FLAGS -fuse-ld=${LD} CACHE STRING "" FORCE)

project(Calculator CXX)
add_library(Calculator SHARED Calculator.cpp)

project(CalculatorTest C)
add_executable(CalculatorTest main.c)
target_link_libraries(CalculatorTest PUBLIC Calculator)

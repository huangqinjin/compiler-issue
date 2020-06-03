cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE "" CACHE STRING "" FORCE)

set(CC "clang" CACHE STRING "Path to clang")
set(VER "" CACHE STRING "Clang version: X.Y")

if (VER)
    set(CMAKE_C_COMPILER ${CC}-${VER})
else()
    set(CMAKE_C_COMPILER ${CC})
endif()

option(FIX OFF "Disable Global Merge")

set(OPT "3" CACHE STRING "Optimization level: 0, 1, 2, 3, s, z")
set_property(CACHE OPT PROPERTY STRINGS 0 1 2 3 s z)

set(ABI "arm" CACHE STRING "ABIs: arm, arm64, x86, x64")
set_property(CACHE ABI PROPERTY STRINGS arm arm64 x86 x64)

if(ABI STREQUAL arm)
    set(TARGET armv7a-unknown-none-eabi)
elseif(ABI STREQUAL arm64)
    set(TARGET aarch64-unknown-none-elf)
elseif(ABI STREQUAL x86)
    set(TARGET i686-unknown-none-gnu)
elseif(ABI STREQUAL x64)
    set(TARGET x86_64-unknown-none-gnu)
elseif(ABI)
    set(TARGET ${ABI})
endif()

project(GlobalMerge C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(${PROJECT_NAME} STATIC flags.c)
target_compile_options(${PROJECT_NAME} PRIVATE -O${OPT} --target=${TARGET})

if (FIX)
    target_compile_options(${PROJECT_NAME} PRIVATE -mno-global-merge)
endif()

find_program(FILTER NAMES grep findstr)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -t $<TARGET_FILE:${PROJECT_NAME}> # | $<SHELL_PATH:${FILTER}> FLAGS_
)

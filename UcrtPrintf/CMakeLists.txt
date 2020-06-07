cmake_minimum_required(VERSION 3.16)
project(UcrtPrintf CXX ASM_MASM)

option(ISO "Use ISO C wide specifiers" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cpp sized.cpp)

# https://docs.microsoft.com/en-us/cpp/assembler/masm/microsoft-macro-assembler-reference
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_sources(${PROJECT_NAME} PRIVATE setup64.asm)
else()
    target_sources(${PROJECT_NAME} PRIVATE setup32.asm)
endif()

if (ISO)
    target_compile_definitions(${PROJECT_NAME} PUBLIC _CRT_STDIO_ISO_WIDE_SPECIFIERS)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC _CRT_STDIO_LEGACY_WIDE_SPECIFIERS)
endif()

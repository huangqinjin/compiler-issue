cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE "" CACHE STRING "" FORCE)

set(CC "clang" CACHE STRING "Path to clang")
set(VER "" CACHE STRING "Clang version: X.Y")

if (VER)
    set(CMAKE_C_COMPILER ${CC}-${VER})
else()
    set(CMAKE_C_COMPILER ${CC})
endif()


project(MemcpyAliasing C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OPT "0" CACHE STRING "Optimization level: 0, 1, 2, 3")
set_property(CACHE OPT PROPERTY STRINGS 0 1 2 3)

add_executable(${PROJECT_NAME} main.c)
target_compile_options(${PROJECT_NAME} PRIVATE -O${OPT})

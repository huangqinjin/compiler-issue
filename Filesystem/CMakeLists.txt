cmake_minimum_required(VERSION 3.16)
project(Filesystem CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(fs INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 9.0)
        # https://gcc.gnu.org/gcc-9/changes.html
        # Using the types and functions in <filesystem> does not require linking with -lstdc++fs now.
        target_compile_options(fs INTERFACE -std=c++17)
    elseif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0)
        # https://gcc.gnu.org/gcc-8/changes.html
        # std::filesystem implementation.
        target_link_libraries(fs INTERFACE stdc++fs)
        target_compile_options(fs INTERFACE -std=c++17)
    elseif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 6.0)
        # https://gcc.gnu.org/gcc-6/changes.html
        # An experimental implementation of the File System TS.
        target_link_libraries(fs INTERFACE stdc++fs)
        target_compile_definitions(fs INTERFACE EXPERIMENTAL)
    else()
        message(FATAL_ERROR "Filesystem is not available in ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES AppleClang)
    # https://developer.apple.com/documentation/xcode_release_notes/xcode_11_release_notes
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0)
        message(FATAL_ERROR "Filesystem is not available in ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    elseif((CMAKE_SYSTEM_NAME MATCHES iOS AND CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL 13) OR
           (CMAKE_SYSTEM_NAME MATCHES tvOS AND CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL 13) OR
           (CMAKE_SYSTEM_NAME MATCHES watchOS AND CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL 6) OR
           (CMAKE_SYSTEM_NAME MATCHES Darwin AND CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL 10.15))
        target_compile_options(fs INTERFACE -std=c++17)
    else()
        message(FATAL_ERROR "Filesystem is not available in ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    target_compile_options(fs INTERFACE -stdlib=libc++)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 9.0)
        # https://releases.llvm.org/9.0.0/projects/libcxx/docs/UsingLibcxx.html#using-filesystem
        target_compile_options(fs INTERFACE -std=c++17)
    elseif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 7.0)
        # https://releases.llvm.org/7.0.0/projects/libcxx/docs/UsingLibcxx.html#using-filesystem-and-libc-fs
        target_link_libraries(fs INTERFACE c++fs)
        target_compile_options(fs INTERFACE -std=c++17)
    elseif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 3.9)
        # https://releases.llvm.org/3.9.0/projects/libcxx/docs/BuildingLibcxx.html#cmdoption-arg-LIBCXX_ENABLE_FILESYSTEM
        target_link_libraries(fs INTERFACE c++experimental)
        target_compile_definitions(fs INTERFACE EXPERIMENTAL)    
    else()
        message(FATAL_ERROR "Filesystem is not available in ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.14)
        target_compile_definitions(fs INTERFACE EXPERIMENTAL)
    else()
        target_compile_options(fs INTERFACE /std:c++17)
    endif()
endif()


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE fs)

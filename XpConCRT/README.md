# Concurrency Runtime on Windows XP

`concrt140.dll` – Concurrency Runtime, shipped via Visual Studio 2015 and later. Required for parallel containers and
algorithms such as `concurrency::parallel_for`. Also, the C++11 STL requires this DLL on Windows XP to power synchronization
primitives, because Windows XP does not have condition variables.

Visual Studio 2012, 2013, 2015 and 2017 contain toolset `v110_xp`, `v120_xp` , `v140_xp` and `v141_xp`, respectively,
to target Windows XP. Visual Studio 2019 still supports targeting Windows XP by setting subsystem minimum version to
5.01 for x86 or 5.02 for x64. But the STL it shipped has removed Windows XP support (`14.26.28801` may be the last version
that still supports Windows XP, but it is in "happens to work" territory, not "supported" territory).

Currently, `CMAKE_GENERATOR_TOOLSET` doesn't support toolset version with `v141_xp`, i.e.
```
cmake -G"Visual Studio 16 2019" -Tv141_xp,host=x64,version=14.26 -AWin32
```
will result in error. To use `v141_xp`, toolset `14.16.27023` must be installed.

Vcpkg doesn't support targeting Windows XP officially and `VCPKG_PLATFORM_TOOLSET` doesn't support specifying toolset
version. To targeting Windows XP, toolset `14.16.27023` must be installed. A workable triplet `x86-windows-xp.cmake`
can be
```
set(VCPKG_CMAKE_SYSTEM_VERSION 5.1)
set(VCPKG_TARGET_ARCHITECTURE x86)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)
set(VCPKG_BUILD_TYPE release)
set(VCPKG_PLATFORM_TOOLSET v141)
set(VCPKG_C_FLAGS "/D_WIN32_WINNT=0x0501 /D_USING_V110_SDK71_ /Zc:threadSafeInit- /I\\\"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Include\\\"")
set(VCPKG_CXX_FLAGS ${VCPKG_C_FLAGS})
set(VCPKG_LINKER_FLAGS "/SUBSYSTEM:CONSOLE,5.01 /LIBPATH:\\\"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib\\\"")
```

A bug about ConCRT on Windows XP is that, initializing ConCRT during DLL loading will cause loader deadlock. To avoid
this issue, delay loading the DLL and initialize ConCRT in main function.

## References

- https://docs.microsoft.com/en-us/cpp/parallel/concrt/overview-of-the-concurrency-runtime
- [Remove XP (and Server 2003) support from STL.](https://github.com/microsoft/STL/pull/1194)
- https://github.com/microsoft/STL/pull/1200
- https://gitlab.kitware.com/cmake/cmake/-/issues/19672
- [[vcpkg] Windows XP support](https://github.com/microsoft/vcpkg/pull/1732)
- [[vcpkg] Allow specifying the exact compiler/toolset version in a triples](https://github.com/microsoft/vcpkg/issues/11317)

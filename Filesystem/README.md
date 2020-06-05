# C++17 File System

GCC and Clang need to link additional library for File System TS or `std::filesystem`. Since GCC 9.0, Clang 9.0, 
AppleClang 11.0, Visual Studio 2017 15.7 and Android NDK 22, `std::filesystem` is fully supported in C++17 without 
linking to any additional libraries.


## References

- https://gcc.gnu.org/gcc-6/changes.html
- https://gcc.gnu.org/gcc-8/changes.html
- https://gcc.gnu.org/gcc-9/changes.html
- https://releases.llvm.org/3.9.0/projects/libcxx/docs/BuildingLibcxx.html#cmdoption-arg-LIBCXX_ENABLE_FILESYSTEM
- https://releases.llvm.org/7.0.0/projects/libcxx/docs/UsingLibcxx.html#using-filesystem-and-libc-fs
- https://releases.llvm.org/9.0.0/projects/libcxx/docs/UsingLibcxx.html#using-filesystem
- https://developer.apple.com/documentation/xcode_release_notes/xcode_11_release_notes
- https://gitlab.kitware.com/cmake/cmake/issues/17834
- https://github.com/android/ndk/issues/609

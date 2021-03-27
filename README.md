# Collection of Compiler Issues

| Issue | Description | Compiler |
|-------|-------------|----------|
| [ExternTemplate](ExternTemplate) | `extern template class` doesn't work for member functions defined inside class | MSVC |
| ~~[NdkLinker](NdkLinker)~~ | NDK linker `bfd` (arm64-v8a default) is very buggy | `lld`: NDK 22 |
| ~~[MemcpyAliasing](MemcpyAliasing)~~ | ~~LLVM wrongly optimizes memcpy on potentially aliased type~~ | ~~Since: Clang 4.0~~<br>Fixed: Clang 8.0 |
| ~~[GlobalMerge](GlobalMerge)~~ | ~~GlobalMerge optimization discards visibility attributes~~ | ~~Since: Clang 4.0~~<br>Fixed: Clang 10.0 |
| ~~[Filesystem](Filesystem)~~ | ~~GCC and Clang need to link additional library for `std::filesystem`~~ | Fixed: GCC 9.0<br>Fixed: Clang 9.0 |
| [UcrtPrintf](UcrtPrintf) | UCRT introduced ISO Mode and Legacy Mode (default) for Formatted IO (`%c`, `%s`) | UCRT |
| [XpConCRT](XpConCRT) | ConCRT may cause loader deadlock on Windows XP | ConCRT |

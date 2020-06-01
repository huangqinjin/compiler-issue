# Collection of Compiler Issues

| Issue | Description | Compiler |
|-------|-------------|----------|
| [ExternTemplate](ExternTemplate) | `extern template class` doesn't work for member functions defined inside class | MSVC |
| [NdkLinker](NdkLinker) | NDK linker `bfd` (arm64-v8a default) is very buggy | NDK |
| ~~[MemcpyAliasing](MemcpyAliasing)~~ | ~~LLVM wrongly optimizes memcpy on potentially aliased type~~ | ~~Since: Clang 4.0~~<br>Fixed: Clang 8.0 |

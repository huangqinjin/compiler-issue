# UCRT Formatted IO

UCRT introduced ISO Mode and Legacy Mode (default) for formatted I/O functions (e.g. `[w]printf`). In Legacy Mode, `%s` 
and `%c` without any length specifiers means the argument is of the "natural" width, i.e., the arguments should be narrow
strings and characters in `printf` and be wide in `wprintf`. In ISO Mode, `%s` and `%c` are always for narrow strings and 
characters. A new length specifier `T` is added, in effect giving the legacy behavior by using `%Ts` and `%Tc`.


## References

- https://docs.microsoft.com/en-us/cpp/porting/overview-of-potential-upgrade-issues-visual-cpp#libraries
- https://docs.microsoft.com/en-us/cpp/porting/visual-cpp-change-history-2003-2015#stdio_and_conio
- https://devblogs.microsoft.com/cppblog/c-runtime-crt-features-fixes-and-breaking-changes-in-visual-studio-14-ctp1/

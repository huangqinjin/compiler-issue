# Memcpy Aliasing

LLVM wrongly optimizes memcpy on potentially aliased type. The bug is introduced in [rL284630](https://reviews.llvm.org/rL284630),
and affects Clang 4.0 up to 7.1, and is fixed by [D44748](https://reviews.llvm.org/D44748).

The bug is found by trying to compile and run [libusb](https://github.com/libusb/libusb) on Android.

| OPT | VER | Error |
|:---:|:---:|:-----:|
|  0  |  *  | No  |
|  1+ | 4.0 | Yes |
|  1+ | 5.0 | Yes |
|  1+ | 6.0 | Yes |
|  1+ | 7.0 | Yes |
|  1+ | 7.1 | Yes |
|  1+ | 8.0+| No  |


## References

- https://issuetracker.google.com/issues/72239989
- https://bugs.llvm.org/show_bug.cgi?id=36228
- https://github.com/android/ndk/issues/652

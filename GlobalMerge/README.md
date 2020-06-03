# GlobalMerge Optimization

The GlobalMerge optimization enabled with `-Oz` or `-O3` discards visibility attributes from variables for ARM32.
The bug affects Clang 7.0 up to 9.1, and is fixed by [D73235](https://reviews.llvm.org/D73235). A workaround for these
affected compilers is to add `-mno-global-merge` to compile options.

| OPT | ABI | FIX | Error |
|:---:|:---:|:---:|:-----:|
| z,3 | arm | OFF | YES |
| z,3 | arm | ON  | No  |


### Normal Output
```
SYMBOL TABLE:
00000000 l    df *ABS*  00000000 flags.c
00000000         .text  00000000 $a.0
00000000 l     d .text  00000000 .text
00000000 g     F .text  00000010 FLAGS_default_get
00000000 g     O .data  00000004 .hidden FLAGS_hidden_1
00000004 g     O .data  00000004 .hidden FLAGS_hidden_2
00000010 g     F .text  00000010 .hidden FLAGS_hidden_set
00000008 g     O .data  00000004 .protected FLAGS_protected_1
0000000c g     O .data  00000004 .protected FLAGS_protected_2
00000020 g     F .text  00000020 .protected FLAGS_protected_add
```

### Error Output
```
SYMBOL TABLE:
00000000 l    df *ABS*  00000000 flags.c
00000000         .text  00000000 $a.0
00000008 l     O .data  00000008 .L_MergedGlobals
00000000 l     d .text  00000000 .text
00000000 l     d .data  00000000 .data
00000000 g     F .text  00000010 FLAGS_default_get
00000000 g     O .data  00000004 .hidden FLAGS_hidden_1
00000008 g     O .data  00000004 FLAGS_hidden_2
00000010 g     F .text  00000010 .hidden FLAGS_hidden_set
00000004 g     O .data  00000004 .protected FLAGS_protected_1
0000000c g     O .data  00000004 FLAGS_protected_2
00000020 g     F .text  00000018 .protected FLAGS_protected_add
```

## References

- https://github.com/android/ndk/issues/829
- https://bugs.llvm.org/show_bug.cgi?id=39413

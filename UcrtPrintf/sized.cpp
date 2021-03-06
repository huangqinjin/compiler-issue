// In this file, all characters and strings format are prepended with proper size specifiers.
// So this file is compatible with both iso and legacy wide specifiers.
#define _CRT_STDIO_ARBITRARY_WIDE_SPECIFIERS
#include <stdio.h>   // _fileno, printf, wprintf
#include <io.h>      // _setmode
#include <fcntl.h>   // _O_WTEXT

extern "C" int __stdcall IsDBCSLeadByte(unsigned char);

// Compatible with ntdef.h
template<typename CharT>
struct STRING
{
    unsigned short Length;
    unsigned short MaximumLength;
    CharT* Buffer;
};

using ANSI_STRING = STRING<char>;
using UNICODE_STRING = STRING<wchar_t>;

template<typename CharT, unsigned short N>
STRING<CharT> RTL_CONSTANT_STRING(const CharT(&s)[N])
{
    return STRING<CharT>{ (N - 1) * sizeof(CharT), N * sizeof(CharT), const_cast<CharT*>(s) };
}

extern "C" void sized()
{
    ANSI_STRING hello = RTL_CONSTANT_STRING("你好");
    UNICODE_STRING world = RTL_CONSTANT_STRING(L"世界");

    fflush(stdout);
    _setmode(_fileno(stdout), _O_TEXT);
    puts("_CRT_STDIO_ARBITRARY_WIDE_SPECIFIERS");
    printf(" printf: [%Ts][%Tc][%ls][%lc]\n", "你好", ',', L"世界", L'！');
    printf(" printf: [%TZ][%Tc][%wZ][%lc]\n", &hello, ',', &world, L'！');

    fflush(stdout);
    _setmode(_fileno(stdout), _O_WTEXT);
    // NOTE: wprintf hs only supports DBCS, see
    // https://github.com/huangqinjin/ucrt/blob/master/inc/corecrt_internal_stdio_output.h#type_case_s_compute_narrow_string_length(int, wchar_t)
    wprintf(L"wprintf: [%hs][%hc][%Ts][%Tc]\n", "你好", ',', L"世界", L'！');
    // NOTE: wprintf hZ only supports ASCII. By hacking Length, hZ can support DBCS.
    for (int i = 0, s = hello.Length; i < s; ++i)
    {
        if (IsDBCSLeadByte((unsigned char)hello.Buffer[i]))
        {
            --hello.Length;
            ++i;
        }
    }
    wprintf(L"wprintf: [%hZ][%hc][%TZ][%Tc]\n", &hello, ',', &world, L'！');
}

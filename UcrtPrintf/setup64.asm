; https://docs.microsoft.com/en-us/cpp/porting/overview-of-potential-upgrade-issues-visual-cpp#libraries
includelib legacy_stdio_definitions.lib

extern printf: PROTO fmt:PTR BYTE, :VARARG
extern setlocale: PROTO category:SDWORD, locale:PTR BYTE

.const
fmt db "ACP locale: %s", 0ah, 0
locale db ".ACP", 0

.code

; Set the locale to the user-default ANSI code page obtained from the
; operating system. This is required for wide/narrow conversion, since
; the locale "C" (set at program startup) cannot handle MBCS.
setup PROC
    push rbp
    mov rbp, rsp
    ; https://docs.microsoft.com/en-us/cpp/build/stack-usage
    ; https://en.wikipedia.org/wiki/X86_calling_conventions#x86-64_calling_conventions
    ; http://lallouslab.net/2016/01/11/introduction-to-writing-x64-assembly-in-visual-studio/
    sub rsp, 20h     ; 32 bytes of shadow space

    mov rcx, 0
    lea rdx, locale
    call setlocale
    cmp rax, 0
    je @F

    lea rcx, fmt
    mov rdx, rax
    call printf
    mov rax, 1
@@:
    mov rsp, rbp
    pop rbp
    ret
setup ENDP

END

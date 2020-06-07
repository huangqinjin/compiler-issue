.686
.model flat, C

; https://docs.microsoft.com/en-us/cpp/porting/overview-of-potential-upgrade-issues-visual-cpp#libraries
includelib legacy_stdio_definitions.lib

extern printf: PROTO C fmt:PTR BYTE, :VARARG
extern setlocale: PROTO C category:SDWORD, locale:PTR BYTE

.const
fmt db "ACP locale: %s", 0ah, 0
locale db ".ACP", 0

.code

; Set the locale to the user-default ANSI code page obtained from the
; operating system. This is required for wide/narrow conversion, since
; the locale "C" (set at program startup) cannot handle MBCS.
setup PROC
    push ebp
    mov ebp, esp

    invoke setlocale, 0, ADDR locale
    cmp eax, 0
    je @F
 
    invoke printf, ADDR fmt, eax
    mov eax, 1
@@:
    mov esp, ebp
    pop ebp
    ret 
setup ENDP

END

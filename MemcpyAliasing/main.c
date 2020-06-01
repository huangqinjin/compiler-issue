#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__attribute__((weak))   // disable inline
void check(int x)
{
    if (x) printf("ERROR: x = %d\n", x);
    exit(x);
}

__attribute__((weak))   // disable inline
void buggy(int one)
{
    unsigned char dst[1] = {1};
    unsigned char src[1] = {0};
    unsigned char *dp = dst;
    unsigned char *sp = src;

    while (1)
    {
        if (one) *dp++ = *sp++;
        else memcpy(dp, sp, 16);
        check(dst[0]);
    }
}

int main()
{
    buggy(1);
}

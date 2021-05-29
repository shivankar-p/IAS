#include <stdio.h>
#include <stdint.h>

int main()
{
    unsigned long int a = 0x2BBCCDDEE;
    unsigned long int b = 0x2BBCCDDEF;
    unsigned __int128 c = (unsigned __int128)a * b;
    printf("[%8.8lX] * [%8.8lX] = [%8.8lX%8.8lX]\n", a, b, (unsigned long int)(c >> 64), (unsigned long int)(c & 0x0FFFFFFFFFFFFFFFF));
    return 0;
}


#include <stdio.h>

int main()
{
    unsigned long int a = 0x2BBCCDDEE;
    printf("[%8.8lX] << 1 = [%8.8lX]\n", a, a << 1);
    return 0;
}


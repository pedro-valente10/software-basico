#include <stdio.h>

unsigned char rotate_left(unsigned char x, int n)
{

    return (x << n) | (x >> (8 - n));
}

int main(void)
{
    unsigned char valor = 0x61;

    printf("Valor original: 0x%02x\n\n", valor);
    printf("Rotate left 1 bit:  0x%02x\n", rotate_left(valor, 1));
    printf("Rotate left 2 bits: 0x%02x\n", rotate_left(valor, 2));
    printf("Rotate left 7 bits: 0x%02x\n", rotate_left(valor, 7));

    return 0;
}
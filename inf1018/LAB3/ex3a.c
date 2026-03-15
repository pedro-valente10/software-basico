#include <stdio.h>

unsigned char switch_byte(unsigned char x) 
{
    return (x >> 4) | (x << 4);
}

int main(void) 
{
    unsigned char teste1 = 0xAB;
    unsigned char teste2 = 0x31;
    unsigned char teste3 = 0xF0;

    printf("original: 0x%02X , trocado: 0x%02X\n", teste1, switch_byte(teste1));
    printf("original: 0x%02X , trocado: 0x%02X\n", teste2, switch_byte(teste2));
    printf("original: 0x%02X , trocado: 0x%02X\n", teste3, switch_byte(teste3));

    return 0;
}
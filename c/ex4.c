/*
Implemente uma função em C, que dado um inteiro sem sinal retorne 
um inteiro sem sinal onde a ordem dos 4 bytes do parâmetro de entrada 
foi invertida. Use o seguinte protótipo: 

unsigned int inverteOrdemBytes(unsigned int i); 

Por exemplo, se a entrada i for igual a 0x01020304 a sáıda devera ser 0x04030201.
*/

#include <stdio.h>

unsigned int inverteOrdemBytes(unsigned int i)
{
    return ((i & 0x000000FF) << 24) |
           ((i & 0x0000FF00) << 8)  |
           ((i & 0x00FF0000) >> 8)  |
           ((i & 0xFF000000) >> 24);
}


int main(void)
{
    unsigned int i;
    i = 16;
    printf("%0x\n", inverteOrdemBytes(i));

    return 0;
}
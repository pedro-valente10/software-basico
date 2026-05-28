#include <stdio.h>

typedef int (*funcp)(int x);

int main() {
    unsigned char codigo[] = {
        0x89, 0xf8, 
        0x83, 0xc0, 0x01,
        0xc3
    };

    funcp f = (funcp)codigo;

    int i = (*f)(10);
    printf("Resultado: %d\n", i);

    return 0;
}
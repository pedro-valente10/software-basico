/*Mesmo que ui seja unsigned, o valor que entrou nele 
veio de uma extensão de sinal de um número negativo.
Logo o resultado de ui será 4294967295*/

#include <stdio.h>

void dump(void *p, int n) {
    unsigned char *p1 = p;
    printf("Endereço binário bytes: ");
    while (n--) {
        printf("[0x%x]", *p1, *p1);
        p1++;
    }
    printf("\n");
}

int main(void) {
    signed char sc = -1; 
    unsigned int ui = sc;

    printf("Valor decimal de char sc: %d\n", sc);
    dump(&sc, sizeof(sc));

    printf("Valor decimal de ui: %u\n", ui);
    printf("Valor hexadecimal: 0x%x\n", ui);
    dump(&ui, sizeof(ui));

    return 0;
}
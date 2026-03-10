#include <stdio.h>

int string2num(char *s, int base) {
    int a = 0;
    int valor_digito;
    for (; *s; s++) {
        char c = (*s);
        if (c >= '0' && c <= '9') {
            valor_digito = c - '0';
        } 
        else if (c >= 'a' && c <= 'z') {
            valor_digito = c - 'a' + 10;
        }
        a = a * base + valor_digito;
    }
    return a;
}

int main(void) {
    printf("%d\n", string2num("1a", 16));
    printf("%d\n", string2num("a09b", 16));
    printf("%d\n", string2num("z09b", 36));

    return 0;
}

//a maior base é 36, pois são 10 dígitos + 26 letras = 36 símbolos
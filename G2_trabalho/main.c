
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "gera_codigo.h"

#define TAMANHO 4096

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Uso: %s arquivo.txt\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if (f == NULL) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    unsigned char *code = mmap(
        NULL,
        TAMANHO,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );

    if (code == MAP_FAILED) {
        perror("Erro ao alocar memoria");
        fclose(f);
        return 1;
    }

    funcp entry = NULL;

    // Gera o codigo de maquina
    gera_codigo(f, code, &entry);

    fclose(f);

    // Como nao temos o tamanho retornado pelo gerador,
    // precisamos identificar o limite de outra maneira.
    // Neste exemplo, usamos um limite fixo.
    int code_size = 100;

    // Salva o codigo binario
    FILE *saida = fopen("codigo.bin", "wb");

    if (saida == NULL) {
        perror("Erro ao criar codigo.bin");
        munmap(code, TAMANHO);
        return 1;
    }

    fwrite(code, 1, code_size, saida);
    fclose(saida);

    // Imprime os bytes ANTES de liberar a memoria
    printf("Codigo de maquina (hexadecimal):\n");

    for (int i = 0; i < code_size; i++) {
        printf("%02X ", code[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }

    printf("\n\n");

    // Habilita execucao
    if (mprotect(code, TAMANHO, PROT_READ | PROT_EXEC) != 0) {
        perror("Erro ao habilitar execucao");
        munmap(code, TAMANHO);
        return 1;
    }

    // Executa a ultima funcao gerada
    if (entry != NULL) {
        int resultado = entry(42);
        printf("Resultado: %d\n", resultado);
    }

    munmap(code, TAMANHO);

    return 0;
}

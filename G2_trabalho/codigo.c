#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

// Tipo de ponteiro para a função gerada: recebe int, retorna int
typedef int (*funcp)(int);

// -----------------------------------------------------------------------------
// FUNÇÕES AUXILIARES DO COMPILADOR
// -----------------------------------------------------------------------------

static int calcula_offset(char tipo, int num) {
    if (tipo == 'p') {
        return -24; // Parâmetro p0
    }
    return -4 * (num + 1); // Variáveis v0, v1, v2...
}

static void carrega_em_eax(unsigned char code[], int *pos, char tipo, int num) {
    if (tipo == '$') {
        code[(*pos)++] = 0xb8;
        *(int *)&code[*pos] = num;
        *pos += 4;
    } else {
        code[(*pos)++] = 0x8b;
        code[(*pos)++] = 0x45;
        code[(*pos)++] = (unsigned char)calcula_offset(tipo, num);
    }
}

static void carrega_em_edi(unsigned char code[], int *pos, char tipo, int num) {
    if (tipo == '$') {
        code[(*pos)++] = 0xbf;
        *(int *)&code[*pos] = num;
        *pos += 4;
    } else {
        code[(*pos)++] = 0x8b;
        code[(*pos)++] = 0x7d;
        code[(*pos)++] = (unsigned char)calcula_offset(tipo, num);
    }
}

static void carrega_em_ecx(unsigned char code[], int *pos, char tipo, int num) {
    if (tipo == '$') {
        code[(*pos)++] = 0xb9;
        *(int *)&code[*pos] = num;
        *pos += 4;
    } else {
        code[(*pos)++] = 0x8b;
        code[(*pos)++] = 0x4d;
        code[(*pos)++] = (unsigned char)calcula_offset(tipo, num);
    }
}

// -----------------------------------------------------------------------------
// COMPILADOR: GERA CÓDIGO DE MÁQUINA
// -----------------------------------------------------------------------------

void gera_codigo(FILE *f, unsigned char code[], funcp *entry) {
    int pos = 0;
    char linha[100];
    int func_index = -1;
    void *enderecos_funcoes[50];

    while (fgets(linha, sizeof(linha), f) != NULL) {

        // 1. INÍCIO DE FUNÇÃO
        if (strncmp(linha, "function", 8) == 0) {
            func_index++;
            enderecos_funcoes[func_index] = (void *)&code[pos];

            code[pos++] = 0x55; // pushq %rbp
            code[pos++] = 0x48; code[pos++] = 0x89; code[pos++] = 0xe5; // movq %rsp, %rbp
            code[pos++] = 0x48; code[pos++] = 0x83; code[pos++] = 0xec; code[pos++] = 0x20; // subq $32, %rsp
            code[pos++] = 0x89; code[pos++] = 0x7d; code[pos++] = 0xe8; // movl %edi, -24(%rbp)
        }

        // 2. RETORNO CONDICIONAL (zret)
        else if (strncmp(linha, "zret", 4) == 0) {
            char t1, t2;
            int n1, n2;
            sscanf(linha, "zret %c%d %c%d", &t1, &n1, &t2, &n2);

            carrega_em_ecx(code, &pos, t1, n1);

            code[pos++] = 0x83; code[pos++] = 0xf9; code[pos++] = 0x00; // cmpl $0, %ecx
            code[pos++] = 0x75; // jne ...
            int tamanho_bloco = (t2 == '$') ? 7 : 5;
            code[pos++] = (unsigned char)tamanho_bloco;

            carrega_em_eax(code, &pos, t2, n2);
            code[pos++] = 0xc9; // leave
            code[pos++] = 0xc3; // ret
        }

        // 3. RETORNO INCONDICIONAL (ret)
        else if (strncmp(linha, "ret", 3) == 0) {
            char t;
            int n;
            sscanf(linha + 4, "%c%d", &t, &n);
            carrega_em_eax(code, &pos, t, n);
            code[pos++] = 0xc9; // leave
            code[pos++] = 0xc3; // ret
        }

        // 4. CHAMADA DE FUNÇÃO (call)
        else if (strstr(linha, "call") != NULL) {
            int v_dest, func_alvo, arg_num;
            char arg_tipo;
            sscanf(linha, "v%d = call %d %c%d", &v_dest, &func_alvo, &arg_tipo, &arg_num);

            carrega_em_edi(code, &pos, arg_tipo, arg_num);

            code[pos++] = 0xe8; // call
            unsigned char *destino = (unsigned char *)enderecos_funcoes[func_alvo];
            unsigned char *proxima = &code[pos + 4];
            int deslocamento = (int)(destino - proxima);

            *(int *)&code[pos] = deslocamento;
            pos += 4;

            code[pos++] = 0x89;
            code[pos++] = 0x45;
            code[pos++] = (unsigned char)calcula_offset('v', v_dest);
        }

        // 5. ATRIBUIÇÃO ARITMÉTICA
        else if (strchr(linha, '=') != NULL) {
            int v_dest;
            char t1, t2, op;
            int n1, n2;

            sscanf(linha, "v%d = %c%d %c %c%d", &v_dest, &t1, &n1, &op, &t2, &n2);
            carrega_em_eax(code, &pos, t1, n1);

            if (op == '+') {
                if (t2 == '$') {
                    code[pos++] = 0x05;
                    *(int *)&code[pos] = n2;
                    pos += 4;
                } else {
                    code[pos++] = 0x03; code[pos++] = 0x45;
                    code[pos++] = (unsigned char)calcula_offset(t2, n2);
                }
            } else if (op == '-') {
                if (t2 == '$') {
                    code[pos++] = 0x2d;
                    *(int *)&code[pos] = n2;
                    pos += 4;
                } else {
                    code[pos++] = 0x2b; code[pos++] = 0x45;
                    code[pos++] = (unsigned char)calcula_offset(t2, n2);
                }
            } else if (op == '*') {
                if (t2 == '$') {
                    code[pos++] = 0x69; code[pos++] = 0xc0;
                    *(int *)&code[pos] = n2;
                    pos += 4;
                } else {
                    code[pos++] = 0x0f; code[pos++] = 0xaf; code[pos++] = 0x45;
                    code[pos++] = (unsigned char)calcula_offset(t2, n2);
                }
            }

            code[pos++] = 0x89;
            code[pos++] = 0x45;
            code[pos++] = (unsigned char)calcula_offset('v', v_dest);
        }
    }

    if (func_index >= 0) {
        *entry = (funcp)enderecos_funcoes[func_index];
    } else {
        *entry = NULL;
    }
}

// -----------------------------------------------------------------------------
// PROGRAMA PRINCIPAL (MAIN COM TESTES)
// -----------------------------------------------------------------------------

int main() {
    FILE *f = fopen("programa.txt", "r");
    if (!f) {
        perror("Erro ao abrir programa.txt");
        return 1;
    }

    // Aloca página de memória com permissão de escrita e execução
    unsigned char *code = mmap(NULL, 4096, PROT_READ | PROT_WRITE | PROT_EXEC,
                               MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (code == MAP_FAILED) {
        perror("Erro no mmap");
        return 1;
    }

    funcp entry = NULL;
    gera_codigo(f, code, &entry);
    fclose(f);

    printf("=== TESTES DE EXECUCAO ===\n");

    // Teste 1: entrada 0 -> deve cair no 'zret' e retornar 99
    int r1 = entry(0);
    printf("Entrada: 0 | Esperado: 99 | Retorno: %d %s\n", r1, (r1 == 99 ? "[OK]" : "[ERRO]"));

    // Teste 2: entrada 10 -> (10 * 2) + 5 = 25
    int r2 = entry(10);
    printf("Entrada: 10 | Esperado: 25 | Retorno: %d %s\n", r2, (r2 == 25 ? "[OK]" : "[ERRO]"));

    // Teste 3: entrada 3 -> (3 * 2) + 5 = 11
    int r3 = entry(3);
    printf("Entrada: 3 | Esperado: 11 | Retorno: %d %s\n", r3, (r3 == 11 ? "[OK]" : "[ERRO]"));

    munmap(code, 4096);
    return 0;
}
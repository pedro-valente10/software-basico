/*Luiz Renato Petry Wieser 2511660  */
/* Pedro Henrique Padilha Valente 2510382 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gera_codigo.h"

#define MAX_VAR 4
#define MAX_FUNCOES 50

/* FUNCAO ERRO */
static void error(const char *msg, int line) {
    fprintf(stderr, "erro: %s na linha %d\n", msg, line);
    exit(EXIT_FAILURE);
}

/* CALCULA OFFSET NA PILHA */
static int calcula_offset(char tipo, int num, int line) {
    if (tipo == 'p') {
        if (num != 0) 
            error("apenas p0 e suportado", line);
        return -24; // p0 fica em -24(%rbp)
    }
    if (tipo == 'v') {
        if (num < 0 || num > MAX_VAR) 
            error("variavel local invalida", line);
        return -4 * (num + 1); // v0=-4, v1=-8, v2=-12...
    }
    error("tipo de dado invalido", line);
    return 0;
}

/* CARREGA EM %eax */
static void carrega_em_eax(unsigned char code[], int *pos, char tipo, int num, int line) {
    if (tipo == '$') {
        code[(*pos)++] = 0xb8; // movl $num, %eax
        *(int *)&code[*pos] = num;
        *pos += 4;
    } else {
        code[(*pos)++] = 0x8b; // movl offset(%rbp), %eax
        code[(*pos)++] = 0x45;
        code[(*pos)++] = (unsigned char)calcula_offset(tipo, num, line);
    }
}

/* CARREGA EM %edi (PARAMETRO) */
static void carrega_em_edi(unsigned char code[], int *pos, char tipo, int num, int line) {
    if (tipo == '$') {
        code[(*pos)++] = 0xbf; // movl $num, %edi
        *(int *)&code[*pos] = num;
        *pos += 4;
    } else {
        code[(*pos)++] = 0x8b; // movl offset(%rbp), %edi
        code[(*pos)++] = 0x7d;
        code[(*pos)++] = (unsigned char)calcula_offset(tipo, num, line);
    }
}

/* CARREGA EM %ecx (TESTE) */
static void carrega_em_ecx(unsigned char code[], int *pos, char tipo, int num, int line) {
    if (tipo == '$') {
        code[(*pos)++] = 0xb9; // movl $num, %ecx
        *(int *)&code[*pos] = num;
        *pos += 4;
    } else {
        code[(*pos)++] = 0x8b; // movl offset(%rbp), %ecx
        code[(*pos)++] = 0x4d;
        code[(*pos)++] = (unsigned char)calcula_offset(tipo, num, line);
    }
}

/* OPERACOES ARITMETICAS */
static void emite_operacao(unsigned char code[], int *pos, char op, char t2, int n2, int line) {
    if (op == '+') {
        if (t2 == '$') {
            code[(*pos)++] = 0x05; // addl $num, %eax
            *(int *)&code[*pos] = n2;
            *pos += 4;
        } else {
            code[(*pos)++] = 0x03; // addl offset(%rbp), %eax
            code[(*pos)++] = 0x45;
            code[(*pos)++] = (unsigned char)calcula_offset(t2, n2, line);
        }
    } else if (op == '-') {
        if (t2 == '$') {
            code[(*pos)++] = 0x2d; // subl $num, %eax
            *(int *)&code[*pos] = n2;
            *pos += 4;
        } else {
            code[(*pos)++] = 0x2b; // subl offset(%rbp), %eax
            code[(*pos)++] = 0x45;
            code[(*pos)++] = (unsigned char)calcula_offset(t2, n2, line);
        }
    } else if (op == '*') {
        if (t2 == '$') {
            code[(*pos)++] = 0x69; // imull $num, %eax, %eax
            code[(*pos)++] = 0xc0;
            *(int *)&code[*pos] = n2;
            *pos += 4;
        } else {
            code[(*pos)++] = 0x0f; // imull offset(%rbp), %eax
            code[(*pos)++] = 0xaf;
            code[(*pos)++] = 0x45;
            code[(*pos)++] = (unsigned char)calcula_offset(t2, n2, line);
        }
    } else {
        error("operador invalido", line);
    }
}

/* GERA CODIGO */
void gera_codigo(FILE *f, unsigned char code[], funcp *entry) {
    int pos = 0;
    int line = 0;
    char linha[128];
    int func_index = -1;
    void *enderecos_funcoes[MAX_FUNCOES];

    while (fgets(linha, sizeof(linha), f) != NULL) {
        line++;

        // ignora linhas em branco
        if (linha[0] == '\n' || linha[0] == '\r')
            continue;

        /* INICIO DA FUNCAO */
        if (strncmp(linha, "function", 8) == 0) {
            func_index++;
            if (func_index >= MAX_FUNCOES)
                error("limite de funcoes excedido", line);

            enderecos_funcoes[func_index] = (void *)&code[pos];

            // prologo da funcao
            code[pos++] = 0x55; // pushq %rbp
            code[pos++] = 0x48; code[pos++] = 0x89; code[pos++] = 0xe5; // movq %rsp, %rbp
            code[pos++] = 0x48; code[pos++] = 0x83; code[pos++] = 0xec; code[pos++] = 0x20; // subq $32, %rsp
            code[pos++] = 0x89; code[pos++] = 0x7d; code[pos++] = 0xe8; // salva p0 em -24(%rbp)
        }

        /* RETORNO CONDICIONAL */
        else if (strncmp(linha, "zret", 4) == 0) {
            char t1, t2;
            int n1, n2;
            if (sscanf(linha, "zret %c%d %c%d", &t1, &n1, &t2, &n2) != 4)
                error("comando invalido", line);

            carrega_em_ecx(code, &pos, t1, n1, line);

            // checa se e zero (cmpl $0, %ecx)
            code[pos++] = 0x83;
            code[pos++] = 0xf9;
            code[pos++] = 0x00;

            // pula o ret se nao for zero (jne)
            code[pos++] = 0x75;
            int tamanho_bloco = (t2 == '$') ? 7 : 5;
            code[pos++] = (unsigned char)tamanho_bloco;

            // bloco de retorno
            carrega_em_eax(code, &pos, t2, n2, line);
            code[pos++] = 0xc9; // leave
            code[pos++] = 0xc3; // ret
        }

        /* RETORNO INCONDICIONAL */
        else if (strncmp(linha, "ret", 3) == 0) {
            char t;
            int n;
            if (sscanf(linha + 4, "%c%d", &t, &n) != 2)
                error("comando invalido", line);

            carrega_em_eax(code, &pos, t, n, line);
            code[pos++] = 0xc9; // leave
            code[pos++] = 0xc3; // ret
        }

        /* CHAMADA DE FUNCAO */
        else if (strstr(linha, "call") != NULL) {
            int v_dest, func_alvo, arg_num;
            char arg_tipo;
            if (sscanf(linha, "v%d = call %d %c%d", &v_dest, &func_alvo, &arg_tipo, &arg_num) != 4)
               error("comando invalido", line);

            if (func_alvo > func_index)
                error("funcao alvo inexistente", line);

            carrega_em_edi(code, &pos, arg_tipo, arg_num, line); // passa argumento

            // call relativo
            code[pos++] = 0xe8;
            unsigned char *destino = (unsigned char *)enderecos_funcoes[func_alvo];
            unsigned char *proxima = &code[pos + 4];
            int deslocamento = (int)(destino - proxima);

            *(int *)&code[pos] = deslocamento;
            pos += 4;

            // salva resultado em v_dest
            code[pos++] = 0x89;
            code[pos++] = 0x45;
            code[pos++] = (unsigned char)calcula_offset('v', v_dest, line);
        }

        /* ATRIBUICAO COM OPERACAO */
        else if (strchr(linha, '=') != NULL) {
            int v_dest;
            char t1, t2, op;
            int n1, n2;

            if (sscanf(linha, "v%d = %c%d %c %c%d", &v_dest, &t1, &n1, &op, &t2, &n2) != 6)
                error("comando invalido", line);

            carrega_em_eax(code, &pos, t1, n1, line);
            emite_operacao(code, &pos, op, t2, n2, line);

            // salva resultado
            code[pos++] = 0x89;
            code[pos++] = 0x45;
            code[pos++] = (unsigned char)calcula_offset('v', v_dest, line);
        }

        /* FIM DA FUNCAO */
        else if (strncmp(linha, "end", 3) == 0) {
            // delimitador
        }

        else {
            error("comando desconhecido", line);
        }
    }

    // retorna a ultima funcao gerada
    if (func_index >= 0) {
        *entry = (funcp)enderecos_funcoes[func_index];
    } else {
        *entry = NULL;
    }
}


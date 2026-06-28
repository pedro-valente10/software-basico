// #include <stdio.h>

// int main(void) {
//     int a[] = {1,2,3,4,5,6,7,8,9,10};
//     for (int i = 0; i < 10; i++) {
//         printf("%d\n", a[i] * a[i]);
//     }


//     return 0;
// }

.data
# Vetor de inteiros (cada 'long' ocupa 4 bytes)
vetor:  .long 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
fmt:    .string "%d\n"

.text
.globl main
main:
    # --- PRÓLOGO ---
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp           # Reserva espaço na pilha
    movq    %rbx, -8(%rbp)      # Salva rbx (usaremos para o índice i)
    movq    %r12, -16(%rbp)     # Salva r12 (usaremos para o endereço base)

    # --- INICIALIZAÇÃO ---
    movl    $0, %ebx            # i = 0 (usando ebx/rbx)
    leaq    vetor(%rip), %r12   # r12 = endereço base de 'vetor'

loop:
    cmpl    $10, %ebx           # Compara i com 10
    jge     fim                 # se i >= 10, sai do loop

    # --- CÁLCULO: a[i] * a[i] ---
    # Pegamos o valor: r12 + (índice * escala de 4 bytes)
    movl    (%r12, %rbx, 4), %eax  # eax = vetor[i]
    imull   %eax, %eax             # eax = eax * eax (quadrado)

    # --- PRINTF ---
    movq    $fmt, %rdi          # 1º param: string de formato
    movl    %eax, %esi          # 2º param: o resultado do cálculo
    movl    $0, %eax            # printf não usa argumentos de ponto flutuante
    call    printf

    # --- INCREMENTO ---
    addl    $1, %ebx            # i++
    jmp     loop                # volta para o início do loop

fim:
    # --- FINALIZAÇÃO ---
    movl    $0, %eax            # return 0
    movq    -16(%rbp), %r12     # recupera r12
    movq    -8(%rbp), %rbx      # recupera rbx
    leave
    ret
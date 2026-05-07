/*int corta(char c1, int b)
{
return c1 + b;
}
*/

/*.text
.globl corta

corta:
    movsbl %dil, %eax
    addl %esi, %eax
    ret*/

.text
.globl buba

buba:
    pushq %rbp          # Salva o frame pointer antigo
    movq  %rsp, %rbp    # Define o novo frame pointer
    pushq %rbx          # Salvaremos %rbx porque vamos usá-lo para 's'
    pushq %r12          # Salvaremos %r12 porque vamos usá-lo para 'i'
    pushq %r13          # Para guardar argumentos que a função 'corta' pode apagar
    pushq %r14

    movq %rdi, %r13     # Move ponteiro 'v' para %r13
    movl %esi, %r14d    # Move 'n' para %r14d
    movl %edx, %r15d    # Move 'c' para %r15d
    
    movl $0, %ebx       # s = 0
    movl $0, %r12d

.L_loop:
    cmpl %r14d, %r12d   # Compara i com n
    jge  .L_done        # Se i >= n, sai do loop

    # if (v[i] <= c)
    movq %r13, %rax     # Pega a base do vetor v
    movslq %r12d, %rcx  # Move 'i' para %rcx expandindo para 64 bits para o índice
    movb (%rax, %rcx), %al # %al = v[i] (carrega 1 byte)
    
    cmpb %r15b, %al     # Compara v[i] com c
    jg   .L_next        # Se v[i] > c, pula para o próximo i

    # s += corta(v[i], n)
    # Preparando argumentos para chamar corta(char, int)
    movsbl %al, %edi    # 1º arg: v[i] (estava em %al)
    movl %r14d, %esi    # 2º arg: n
    call corta          # Chama a função. Resultado volta em %eax
    addl %eax, %ebx     # s += resultado do corta

.L_next:
    incl %r12d          # i++
    jmp  .L_loop        # Volta para o início do loop

.L_done:
    movl %ebx, %eax     # Move a soma final 's' para o registrador de retorno
    
    popq %r14           # Restaura tudo na ordem inversa
    popq %r13
    popq %r12
    popq %rbx
    popq %rbp
    ret

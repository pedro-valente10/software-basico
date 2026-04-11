.section .data
    nums:   .long 65, -105, 111, 34    # Array de ints (4 bytes cada)
    fmt:    .string "soma = %d\n"      # String de formato para o printf

.section .text
.globl main

main:
    pushq %rbp                # Prólogo
    movq  %rsp, %rbp

    movl  $0, %ebx            # %ebx será nossa variável 's' (soma = 0)
    movl  $0, %ecx            # %ecx será nossa variável 'i' (índice = 0)

loop:
    cmpl  $4, %ecx            # Compara i com 4
    jge   final_loop          # Se i >= 4, sai do loop

    # Cálculo do endereço: end(nums[i]) = nums + i * 4
    # Usamos movslq para converter o índice i (32 bits) para 64 bits em %rax
    movslq %ecx, %rax         
    
    # Pegamos o valor em nums + (rax * 4) e somamos em %ebx (soma)
    addl  nums(,%rax,4), %ebx

    incl  %ecx                # i++
    jmp   loop                # Volta para o início do loop

final_loop:
    # Preparação para o printf: printf(fmt, s)
    movq  $fmt, %rdi          # 1º argumento: string de formato
    movl  %ebx, %esi          # 2º argumento: valor da soma
    movl  $0, %eax            # %eax deve ser 0 para funções variádicas (printf)
    call  printf

    movl  $0, %eax            # return 0
    leave                     # Epílogo (movq %rbp, %rsp; popq %rbp)
    ret
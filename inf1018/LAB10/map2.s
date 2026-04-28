/*int f(int x);

void map2 (int* um, int *outro, int n) {
  int i;
  for (i=0; i<n; i++)
    *(outro+i) = f(*(um+i));
}*/

.text
.globl map2

map2:
    # %rdi: int* um
    # %rsi: int* outro
    # %edx: int n

    pushq   %rbp
    movq    %rsp, %rbp
    pushq   %rbx                # %rbx para armazenar 'i'
    pushq   %r12                # %r12 para 'um'
    pushq   %r13                # %r13 para 'outro'
    pushq   %r14

    movq    %rdi, %r12
    movq    %rsi, %r13
    movl    %edx, %r14d
    movl    $0, %ebx

.L_loop:
    cmpl    %r14d, %ebx         # Compara i com n
    jge     .L_done

    movl    (%r12, %rbx, 4), %edi
    call    f

    movl    %eax, (%r13, %rbx, 4)
    incl    %ebx   # i++
    jmp     .L_loop

.L_done:
    popq    %r14
    popq    %r13
    popq    %r12
    popq    %rbx
    popq    %rbp
    ret

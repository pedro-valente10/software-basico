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
    pushq   %r14d
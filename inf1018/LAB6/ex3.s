/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  for (i = 0, p = nums; i != 4; i++, p++)
    if ((*p % 2) == 0)
      printf("%d\n", *p);
  return 0;
}
*/

.data
nums: .long 10, -21, -30, 45
fmt:  .string "%d\n"

.text
.globl main
main:
    pushq %rbp
    movq  %rsp, %rbp
    
    # Salvando registradores que o printf pode destruir
    pushq %rbx                      # Usaremos %ebx para 'i'
    pushq %r12                      # Usaremos %r12 para 'p'

    movl $0, %ebx                   # i = 0
    leaq nums(%rip), %r12           # p = nums (carrega o endereço)

loop:
    cmpl $4, %ebx                   # i != 4?
    je end_loop

    movl (%r12), %r13d              # Move *p para %r13d (temporário)
    
    # Teste de paridade: (*p & 1)
    testl $1, %r13d                 # Aplica AND bit a bit com 1
    jne next_iter                   # Se o resultado NÃO for zero, o bit 0 era 1 (ímpar)

    # Se chegou aqui, é par
    movq $fmt, %rdi                 # 1º arg: formato
    movl %r13d, %esi                # 2º arg: o valor de *p
    movl $0, %eax                   # 0 vetores flutuantes
    call printf

next_iter:
    addl $1, %ebx                   # i++
    addq $4, %r12                   # p++ (pulo de 4 bytes)
    jmp loop

end_loop:
    movl $0, %eax                   # return 0
    popq %r12
    popq %rbx
    popq %rbp
    ret

.section .note.GNU-stack,"",@progbits
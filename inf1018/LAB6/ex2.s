/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  int sum = 0;
  for (i = 0, p = nums; i != 4; i++, p++)
    sum += *p;
  printf("%d\n", sum);
  return 0;
}
*/

.data
nums: .long 10, -21, -30, 45        # int nums[] = {10, -21, -30, 45}
fmt:  .string "%d\n"         

.text
.globl main
main:
    pushq %rbp                    
    movq  %rsp, %rbp
    
    # Salvando registradores callee-saved que vamos usar
    pushq %rbx                      
    pushq %r12
    pushq %r13                      # %r13d para a variável 'sum'

    # Inicialização
    movl $0, %ebx                   # i = 0
    movq $nums, %r12                # p = nums
    movl $0, %r13d                  # sum = 0

L1:
    cmpl $4, %ebx                   # i != 4 ?
    je L2                           # Se i == 4, sai do loop

    addl (%r12), %r13d              # sum += *p (leitura de 4 bytes)
    
    addl $1, %ebx                   # i++
    addq $4, %r12                   # p++ (anda 4 bytes, pois p é int*)
    jmp L1

L2:
    # Chamada do printf("%d\n", sum)
    movq $fmt, %rdi                 
    movl %r13d, %esi              
    movl $0, %eax                  
    call printf

    # Restauração e retorno
    movl $0, %eax                   # return 0
    
    popq %r13
    popq %r12
    popq %rbx
    popq %rbp
    ret
/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  for (i = 0, p = nums; i != 4; i++, p++)
    printf("%d\n", *p);
  return 0;
}
*/

.data
nums:  .byte  10, -21, -30, 45    # Array de bytes
Sf:    .string "%d\n"

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
/********************************************************/

  movl  $0, %ebx          # i = 0
  movq  $nums, %r12       # p = &nums

L1:
  cmpl  $4, %ebx          # i == 4?
  je  L2

  # MODIFICAÇÃO 1: Pegar apenas 1 byte e estender o sinal para 32 bits
  movsbl (%r12), %eax     # eax = (int) *p (byte -> long com sinal)

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi       
  movl    %eax, %esi      
  call  printf            
/*************************************************************/

  addl  $1, %ebx          # i++
  
  # MODIFICAÇÃO 2: Incrementar o ponteiro em apenas 1 byte
  addq  $1, %r12          # p++ (próximo byte)
  
  jmp  L1

L2:  
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax          
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/***************************************************************/
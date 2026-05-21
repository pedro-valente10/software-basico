/*int novonum(void) {
  int minhalocal;
  printf("numero: ");
  scanf("%d",&minhalocal);
  return minhalocal;
}*/

.data
    entrada_str:
        .string "numero: "
    saida_str:
        .string "%d"

.text
.globl novonum

novonum:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp

    leaq    entrada_str(%rip), %rdi
    movl    $0, %eax
    call    printf@PLT

    leaq    -4(%rbp), %rsi
    leaq    saida_str(%rip), %rdi
    movl    $0, %eax
    call    __isoc99_scanf@PLT

    movl    -4(%rbp), %eax

    movq %rbp, %rsp
    popq %rbp
    ret

/*
struct X {
  int vi;
  double vd;
  struct X *next;
};

double pack (struct X *px) {
  double acc = 0;
  while (px != NULL) {
    acc += foo(px->vd, px->vi);
    px = px->next;
  }
  return acc;
}
*/

/*
*px = %rdi
aux = %r8d
double acc = %xmm0

*/

.text
.globl pack

pack:
  pushq %rbp
  movq %rsp, %rbp
  subq $16, %rsp

  movl $0, %r8d
  cvtsi2sd %r8d, %xmm0

loop:
  testq %rdi, %rdi
  je .fim

  # 1. Preparar argumentos para
  movl 0(%rdi), %edi
  movsd 8(%rdi), %xmm0

  # 2. Salvar estado antes de chamar foo
  pushq %rdi
  subq $8, %rsp
  
  call foo

  # 3. Restaurar estado
  addq    $8, %rsp
  popq    %rdi

  addsd   %xmm0, %xmm1
  movq    16(%rdi), %rdi
  jmp     loop

.fim:
  movsd %xmm1, %xmm0
  leave
  ret
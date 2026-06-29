/*
struct X1 {
  int vi;
  float vf;
};

double pack1 (struct X1 *px, int n) {
  double acc = 0;
  int i;
  for (i=0;i<n;i++)
    acc += foo(px[i].vf, px[i].vi);
  return acc;
}
*/

/*
*px = %rdi
int n = %esi
double acc = %xmm0
aux = %r8d
int i = %rbx

int vi = %edi
float vf = %xmm1

*/

.text
.globl pack1

pack1:
# criando a pilha
  pushq %rbp
  movq %rsp, %rbp

  #alocando espaço para variaveis importantes
  pushq %rbx
  pushq %r12
  pushq %r13
  subq $24, %rsp

  # salvando em callee-saved
  movq %rdi, %r12
  movl %esi, %r13d

  # acc
  movl $0, %r8d
  cvtsi2sd %r8d, %xmm0
  movsd %xmm0, -32(%rbp)

  movq $0, %rbx

.loop:
  cmpl %r13d, %ebx
  jge .fim

  movss 4(%r12, %rbx, 8), %xmm0
  movl 0(%rdi, %rbx, 8), %edi

  call foo

  movsd -32(%rbp), %xmm1
  addsd %xmm0, %xmm1
  movsd %xmm1, -32(%rbp)

  incl %ebx
  jmp .loop

.fim:
  movsd -32(%rbp), %xmm0

  addq $24, %rsp
  popq %r13
  popq %r12
  popq %rbx

  leave
  ret



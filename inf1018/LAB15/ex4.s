/*
double foo3 (double *a, int n) {
  int i;
  double r = 0.0;
  for (i=0; i<n; i++) {
    r += sin(*a);
    a++;
  }
  return r;
}
*/

.text
.global foo3

foo3:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $48, %rsp

    movq    %rbx, -8(%rbp)
    movq    %r12, -16(%rbp)
    movq    %r13, -24(%rbp)

    movq    %rdi, %r12
    movl    %esi, %ebx

    pxor    %xmm0, %xmm0
    movsd   %xmm0, -32(%rbp)

    xorl    %r13d, %r13d

.L_cond:
    cmpl    %ebx, %r13d
    jge     .L_end

    movsd   (%r12), %xmm0
    call    sin@PLT

    movsd   -32(%rbp), %xmm1
    addsd   %xmm0, %xmm1
    movsd   %xmm1, -32(%rbp)

    addq    $8, %r12
    incl    %r13d
    jmp     .L_cond

.L_end:
    movsd   -32(%rbp), %xmm0

    movq    -8(%rbp), %rbx
    movq    -16(%rbp), %r12
    movq    -24(%rbp), %r13

    leave
    ret

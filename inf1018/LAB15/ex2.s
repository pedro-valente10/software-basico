/*float foo1 (float a, float b) {
  return sin(a) + b;
}*/

.text
.globl foo1

foo1:
    pushq   %rbp
    movq    %rsp, %rbp

    subq    $16, %rsp

    movss   %xmm1, -4(%rbp)
    cvtss2sd %xmm0, %xmm0
    call sin@PLT

    cvtss2sd -4(%rbp), %xmm1
    addsd   %xmm1, %xmm0


    cvtsd2ss %xmm0, %xmm0
    leave
    ret
    
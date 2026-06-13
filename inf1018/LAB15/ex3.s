/*double foo2 (float a, float b) {
  return sin(a) + cos(b);
}*/

.text
.globl foo2

foo2:
    pushq   %rbp
    movq    %rsp, %rbp

    subq    $16, %rsp

    movss   %xmm1, -4(%rbp)

    cvtss2sd %xmm0, %xmm0
    call    sin@PLT

    movsd   %xmm0, -16(%rbp)

    cvtss2sd -4(%rbp), %xmm0
    call    cos@PLT
    
    movsd   -16(%rbp), %xmm1
    
    addsd   %xmm1, %xmm0

    leave
    ret
    
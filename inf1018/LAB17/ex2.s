/*
double foo (double a, int b) {
  return a * (-b);
}
*/

.text
.globl foo

foo:
    negl %edi
    cvtsi2sd %edi, %xmm1
    mulsd %xmm1, %xmm0
    ret

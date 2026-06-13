/*float foo (double a, float b) {
  return (a+b)*(a-b);
}*/

.text
.globl foo

foo:
  cvtss2sd    %xmm1, %xmm2
  movapd      %xmm0, %xmm3
  addsd       %xmm2, %xmm3

  subsd       %xmm2, %xmm0

  mulsd       %xmm3, %xmm0

  cvtsd2ss    %xmm0, %xmm0
  ret

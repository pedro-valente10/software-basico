/*int fat (int n) {
  if (n==0) return 1;
  else return n*fat(n-1);
}*/

.text
.globl fat

fat:
  cmpl $0, %edi
  jne .L_recursao

  movl $1, %eax
  ret

.L_recursao:
  pushq %rdi
  subl $1, %edi
  call fat

  popq %rdi
  imull %edi, %eax
  ret


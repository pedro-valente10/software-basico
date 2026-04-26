/*void foo (int a[], int n) {
  int i;
  int s = 0;
  for (i=0; i<n; i++) {
    s += a[i];
    if (a[i] == 0) {
      a[i] = s;
      s = 0;
    }
  }
}*/

.text
.globl foo

foo:
  movl $0, %ecx
  movl $0, %edx

.L_loop:
  cmpl %esi, %ecx
  jge .L_done

  movl (%rdi, %rcx, 4), %r8d
  addl %r8d, %edx

  testl %r8d, %r8d
  jne .L_next

  movl %edx, (%rdi, %rcx, 4)
  movl $0, %edx

.L_next:
  incl %ecx
  jmp .L_loop

.L_done:
  ret


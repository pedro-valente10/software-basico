/*struct X {
  int val;
  struct X *next;
};

int add (struct X *x) {
  int a = 0;
  for (; x != NULL; x = x->next)
    a += x->val;
  return a;
}*/

.text
.globl add

add:
    movl $0, %eax

.L_loop:
    testq %rdi, %rdi
    je .L_done

    addl (%rdi), %eax
    movq 8(%rdi), %rdi

    jmp .L_loop

.L_done:
    ret



/*int add2 (struct X *x) {
  if (x == NULL) return 0;
  else return x->val + add2(x->next);
}*/

.text
.globl add2

add2:
    testq %rdi, %rdi
    je .L_done1

    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    subq $8, %rsp

    movl (%rdi), %ebx 
    movq 8(%rdi), %rdi
    call add2

    addl %ebx, %eax
    addq $8, %rsp
    popq %rbx
    popq %rbp
    ret

.L_done1:
    movl $0, %eax
    ret



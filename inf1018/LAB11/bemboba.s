/*int bemboba (int num) {
  int local[4];
  int *a;
  int i;

  for (i=0,a=local;i<4;i++) {
    *a = num;
    a++;
  }
  return addl (local, 4);
}
*/

.text
.globl bemboba

bemboba:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp       

    movl    $0, %ecx
    leaq    -16(%rbp), %rdx

.L_loop:
    cmpl    $4, %ecx
    jge     .L_loop_end

    movl    %edi, (%rdx)
    addq    $4, %rdx 
    incl    %ecx
    jmp     .L_loop

.L_loop_end:
    leaq    -16(%rbp), %rdi
    movl    $4, %esi
    call    addl

    leave
    ret

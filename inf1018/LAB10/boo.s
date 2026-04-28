/*struct X {
  int val1;
  int val2;
};

int f(int i, int v);

void boo (struct X *px, int n, int val) {
  while (n--) {
    px->val2 = f(px->val1, val);
    px++;
  }
}*/

.text
.globl boo

boo:
  # px  em %rdi (ponteiro para struct X)
  # n   em %esi (inteiro de 32 bits)
  # val em %edx (inteiro de 32 bits)
  
.L_loop:
  testl %esi, %esi
  je .L_done
  decl %esi

  pushq %rdi
  pushq %rsi
  pushq %rdx

  movl (%rdi), %edi
  movl %edx, %esi
  call f

  popq %rdx
  popq %rsi
  popq %rdi

  movl %eax, 4(%rdi)
  addq $8, %rdi

  jmp .L_loop

.L_done:
  ret

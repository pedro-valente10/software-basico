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

    # --- Alocação de Espaço na Pilha ---
    # local[4] precisa de 16 bytes (4 ints * 4 bytes).
    # Subtraímos 16 do %rsp para abrir esse espaço.
    subq    $16, %rsp       

    # --- Inicialização do Loop ---
    movl    $0, %ecx
    leaq    -16(%rbp), %rdx

.L_loop:
    cmpl    $4, %ecx
    jge     .L_loop_end

    # --- Corpo do Loop ---
    movl    %edi, (%rdx)
    addq    $4, %rdx 
    incl    %ecx
    jmp     .L_loop

.L_loop_end:
    # --- Preparação para chamar addl(local, 4) ---
    leaq    -16(%rbp), %rdi
    movl    $4, %esi
    call    addl

    # --- Finalização da Função ---
    leave
    ret

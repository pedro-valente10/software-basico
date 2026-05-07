/*int novonum(void) {
  int minhalocal;
  printf("numero: ");
  scanf("%d",&minhalocal);
  return minhalocal;
}*/

.data
    entrada_str:
        .string "numero: "
    saida_str:
        .string "%d"

.text
.globl novonum

novonum:
    # --- Prólogo da Função ---
    pushq   %rbp                # Salva o frame pointer antigo
    movq    %rsp, %rbp          # Define o novo frame pointer
    subq    $16, %rsp           # Aloca 16 bytes na pilha (minhalocal + alinhamento)

    # --- printf("numero: ") ---
    leaq    entrada_str(%rip), %rdi # Carrega o endereço da string no 1º argumento
    movl    $0, %eax            # printf espera 0 em AL para funções sem ponto flutuante
    call    printf@PLT

    # --- scanf("%d", &minhalocal) ---
    leaq    -4(%rbp), %rsi      # Endereço de 'minhalocal' (localizada a -4 do RBP)
    leaq    saida_str(%rip), %rdi # Primeiro argumento: string de entradao
    movl    $0, %eax            # Limpa EAX para a chamada
    call    __isoc99_scanf@PLT

    # --- return minhalocal ---
    movl    -4(%rbp), %eax      # Move o valor da variável para EAX (registrador de retorno)

    # --- Epílogo da Função ---
    leave                       # Equivale a 'movq %rbp, %rsp' e 'popq %rbp'
    ret

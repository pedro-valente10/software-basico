// #include <stdio.h>

// char S2[] = {65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0};
// int main (void) {
//   char *pc = S2;
//   while (*pc) {
//     if ((*pc) != 123 && (*pc) != 125)
//         printf ("%c", *pc);
//     pc++;
//     }

//     printf("\n");
//     return 0;
// }

.data
S2:  .byte 65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0
Sf:  .string "%c"    /* primeira string de formato para printf */
Sf2: .string "\n"    /* segunda string de formato para printf */

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)  /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */
/********************************************************/

  movq  $S2, %r12  /* r12 = pc (ponteiro para a string) */

L1:
  movb  (%r12), %bl      /* Move o caractere atual para %bl */
  cmpb  $0, %bl          /* if (*pc == 0) ? */
  je  L2                 /* Se fim da string, vai para L2 */

  /* Implementação do if ((*pc) != 123 && (*pc) != 125) */
  cmpb  $123, %bl        /* Compara com '{' */
  je  proximo            /* Se for igual, pula a impressão */
  
  cmpb  $125, %bl        /* Compara com '}' */
  je  proximo            /* Se for igual, pula a impressão */

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movsbl  %bl, %eax      /* estendendo o byte para 32 bits para o printf */
  movq    $Sf, %rdi      /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi     /* segundo parametro  (inteiro) */
  movl  $0, %eax
  call  printf           /* chama a funcao da biblioteca */
/*************************************************************/

proximo:
  addq  $1, %r12         /* pc++ */
  jmp  L1                /* goto L1; */

L2:  
/*************************************************************/
/* este trecho imprime o \n (estraga %eax)                  */
  movq    $Sf2, %rdi    /* primeiro parametro (ponteiro)*/
  movl  $0, %eax
  call  printf           /* chama a funcao da biblioteca */
/*************************************************************/

/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq    -16(%rbp), %r12 /* recupera r12 */
  movq    -8(%rbp), %rbx  /* recupera rbx */
  leave
  ret      
/***************************************************************/
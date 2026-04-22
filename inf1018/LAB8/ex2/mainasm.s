.data
  nums: .int 3, -5, 7, 8, -2
  s1:   .string "%d\n"

  .text
  .globl main
  main:
  /* prologo */
     pushq %rbp
     movq  %rsp, %rbp
     subq  $16, %rsp
     movq  %rbx, -8(%rbp)     /* Usaremos %rbx para o contador 'i' */
     movq  %r12, -16(%rbp)    /* Usaremos %r12 para o ponteiro 'p' */

  /* Inicialização */
     movl  $0, %ebx           /* i = 0 */
     movq  $nums, %r12        /* p = nums */

  loop:
     cmpl  $5, %ebx           /* i < 5? */
     jge   fim_loop           /* se i >= 5, sai */

     /* Prepara chamada: filtro(*p, LIM) */
     movl  (%r12), %edi       /* primeiro arg: *p (valor apontado) */
     movl  $1, %esi           /* segundo arg: LIM (que é 1) */
     call  filtro             /* o retorno estará em %eax */

     /* Prepara chamada: printf("%d\n", retorno_do_filtro) */
     movq  $s1, %rdi          /* primeiro arg: formato da string */
     movl  %eax, %esi         /* segundo arg: o resultado de filtro() */
     movl  $0, %eax           /* printf precisa de %eax zerado para varargs */
     call  printf

     /* Atualizações */
     addl  $1, %ebx           /* i++ */
     addq  $4, %r12           /* p++ (avança 4 bytes pois é um int*) */
     jmp   loop

  fim_loop:
     movl  $0, %eax           /* return 0 */

  /* finalizacao */
     movq -8(%rbp), %rbx
     movq -16(%rbp), %r12
     leave
     ret
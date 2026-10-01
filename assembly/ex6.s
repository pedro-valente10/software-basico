/*
struct X {
  int val;
  struct X *next;
};

int add (struct X *x) {
  int a = 0;
  for (; x != NULL; x = x->next)
    a += x->val;
  return a;
}
*/

.text
.globl add

add:
    movl $0, %eax

.loop:
    testq %rdi, %rdi
    je .fim

    movl (%rdi), %ecx
    addl %ecx, %eax

    movq 8(%rdi), %rdi
    jmp .loop

.fim:
    ret


/*
o que aconteceu exatamente foi:

"a" é o valor de retorno e é inicializado valendo zero,
então colocamos $0 em %eax, pois a função retorna um inteiro

após isso, verificamos se X (o struct) é igual a NULL.
Se for igual, pulamos para o .fim. Se não, prosseguimos no .loop.

utilizamos uma variável temporária aleatória (%ecx), onde guardamos o valor inteiro
que está dentro da struct (val). Depois disso, fazemos:
%eax = %eax + %ecx
para cada iteração, estamos atualizando o valor de %eax e modificando o valor de %ecx

analisando a estrutua do struct, percebemos que existe apenas um interio dentro dele (4 bytes),
portanto os demais 4 bytes que completam os 8, são padding (PP). Assim, basta andar de 8 em bytes
para avançar entre cada nó (struct). Ou seja: movq 8(%rdi), %rdi

Após chegar no próximo nó, repetimos o .loop.

Por fim, retornamos o valor final em %eax

*/
/*float foo (double a, float b) {
  return (a+b)*(a-b);
}*/


.text
.globl foo

foo:
    #xmm1 e xmm2 = float b
    #xmm0 e xmm3 = double a

    cvts2sd %xmm1, %xmm2
s
    movapd %xmm0, %xmm3
    addsd %xmm2, %xmm3

    subsd %xmm2, %xmm0

    mulsd %xmm3, %xmm0

    cvtsd2ss %xmm0, %xmm0
    ret


/*
O que aconteceu exatamente foi:

A função em C recebe parâmetros do tipo double e float.
O primeiro parâmetro fica em %xmm0 e o segundo em %xmm1

pela variação de bytes que cada um desses tipos tem (8 e 4 bytes, respectivamente),
não podemos fazer operações aritiméticas direto sobre elas, pois estaríamos usando
lixo de memória ou perdendo valor. 

Assim, convertemos o float para double.
Como vamos precisar de %xmm0 duas vezes, uma para fazer a conta de adição e outra de 
subtração, fazemos uma cópia do seu valor.

Depois disso, podemos fazer as operações aritiméticas normalmente com os registradores
corretos e tomando cuidado com a ordem de salvamento dos osperadores, que segue o padrão:

addsd %xmm2, %xmm3 ---> dest = src + dest
                          |     |      |
                        %xmm3 %xmm2  %xmm3

xmm3 aramzena o valor de soma.
Depois
xmm0 armaezena o valor da subtração

xmm3 é multiplicado com xmm0 e o valor é salvo em xmm0

Por fim:
xmm0 é convertido em float, pois a função em C retorna float, não double

E retornamos xmm0

*/

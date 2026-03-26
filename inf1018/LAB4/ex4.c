/* programa 3*/
#include <stdio.h>

int main (void) {
  int x = 0xffffffff;
  unsigned int y = 2;
  printf("x=%d, y=%d\n", x, y);
  printf("x é menor do que y? %s\n", (x<y)?"sim":"nao");
  return 0;
}

/*no primeiro programa, a variavel x é do tipo int 
e como o seu bit mais significativo (o mais à esquerda)
é 1, o valor torna-se negativo

no prgrama 2, ele não está comparando "-1" da variavel x com "2"
da variavel y. Ele está comparando 4.294.967.295 com 2, que é maior

no programa 3, a hierarquia da lingaugem C faz com que, quando x é
comparado y, o int x torna-se do tipo unsigned int*/
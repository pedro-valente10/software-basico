#include <ctype.h>
#include <stdio.h>

int string2num (char *s) {
  int a = 0;
  for (; *s; s++)
    a = a*10 + (*s - '0');
  return a;
}

int main (void) {
  printf("==> %d\n", string2num("1234"));
  printf("==> %d\n", string2num("1234") + 1);
  printf("==> %d\n", string2num("1234") + string2num("1"));
  return 0;
}

//*s indica que a repetição continuará enquanto o último caractere no array não for \0, ou seja, enquanto for verdadeiro
//para cada iteração, *s - 0 isola o valor numérico associado a *s
//o valor de 'a' é inicializado como '0' e o seu valor muda a cada iteração
//preservando também os numeros anteriores que já foram encontrados nas operações anteriores

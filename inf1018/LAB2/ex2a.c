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

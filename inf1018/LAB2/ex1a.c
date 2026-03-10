#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

int main (void) {
  int i  = 10000;
  dump(&i, sizeof(i));
  return 0;
}

//há 4 bytes em uma variável do tipo inteiro, 8 em um long e 2 em um short
//cada linha que foi impressa é a quantidade de bytes da variável i
//O ponteiro p1 caminha de 1 em 1 byte por causa do char

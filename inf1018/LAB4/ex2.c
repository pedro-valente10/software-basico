#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

int main (void) {
  short l = -32765;
  unsigned short k = 32771;
  printf("l=%d, k=%u \n", l, k);
  printf("dump de l: \n");
  dump(&l, sizeof(l));
  printf("dump de k: \n");
  dump(&k, sizeof(k));
  return 0;
}

/*
saida esperada:
dump de l: 
0x7ff... - 03
0x7ff...f1 - 80
dump de k: 
0x7ff... - 03
0x7ff... - 80

Ao fazer p1++, você está andando 
exatamente 1 byte de cada vez na memória, revelando
 como o short (que tem 2 bytes) está deitado nos endereços físicos.
*/
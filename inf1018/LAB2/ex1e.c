#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

int main (void) {
  char p[] = "$";
  dump(p, sizeof(p));
  return 0;

}

//A em hexadecimal é equivalente a 41 na tabela ASCII
//" " em hexadecimal é equivalente a 20 na tabela ASCII
//, em hexadecimal é equivalente a 2c na tabela ASCII
//\n em hexadecimal é equivalente a 0a na tabela ASCII
//$ em hexadecimal é equivalente a 24 na tabela ASCII
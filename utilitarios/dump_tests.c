#include <stdio.h>
void dump(void *p, int n) {
  unsigned char *p1 = (unsigned char *)p;
  while (n--) {
    printf("%p - %02x\n",p1,*p1);
    p1++;
  }
}

struct X {
  double d;
  float  f;
  short  s;
} x;


int main(void) {
  x.d = -4.5;
  dump(&x, sizeof(x));
  return 0;
}
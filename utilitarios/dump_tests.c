#include <stdio.h>
void dump (void *p, int n) {
unsigned char *p1 = (unsigned char *) p;
while (n--) {
printf("%p - %02x\n", p1, *p1);
p1++;
}
}
struct S {
int a;
float *b;
char c;
double d;
float e;
} s = {-62, &s.e, 62, 62.625, 62.625};
int main(void) {
dump(&s, sizeof(struct S));
return 0;
}
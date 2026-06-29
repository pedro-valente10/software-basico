#include <stdio.h>

struct X {
  int vi;
  double vd;
  struct X *next;
};

double pack(struct X *px);
double foo(double a, int b);

int main(void)
{
    printf("%f\n", pack(&(struct X){7, 2.0, NULL}));

    return 0;
}
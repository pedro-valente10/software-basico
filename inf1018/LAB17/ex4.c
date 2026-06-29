#include <stdio.h>

struct X1 {
  int vi;
  float vf;
};

float pack1(struct X1 *px1);
double foo(double a, int b);

int main(void)
{
    printf("%f\n", pack1(&(struct X1){7, 2.0}));

    return 0;
}
#include <stdio.h>
#include <math.h>

double foo2(float a, float b);

int main() {
    double a = M_PI;
    double b = M_PI_2;

    double resultado_esperado = sin(a) + cos(b);
    printf("Resultado Esperado: %f\n", resultado_esperado);

    return 0;
}
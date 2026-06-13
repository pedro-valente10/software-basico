#include <stdio.h>
#include <math.h>

float foo1(float a, float b);

int main() {
    float a = M_PI;
    float b = M_PI_2;

    float resultado_esperado = (float)sin((double)a) + b;
    printf("Resultado Esperado: %f\n", resultado_esperado);

    return 0;
}
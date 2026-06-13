#include <stdio.h>

float foo(double a, float b);

int main(void)
{
    double x = 5.0;
    float y = 3.0;
    
    float resultado = foo(x, y);
    
    printf("Resultado esperado: (5+3)*(5-3) = 8 * 2 = 16.000000\n");
    printf("Resultado obtido:   %f\n", resultado);

    return 0;
}
#include <stdio.h>
#include <math.h>

extern double foo3(double *a, int n);

int main() {
    double valores[] = {0.0, M_PI_2, M_PI, 3.0 * M_PI_2, 2.0 * M_PI};

    int n = sizeof(valores) / sizeof(valores[0]);

    double resultado_esperado = foo3(valores, n);
    for (int i = 0; i < n; i++) {
        resultado_esperado += sin(valores[i]);
    }

    printf("Resultado Esperado: %f\n", resultado_esperado);

    return 0;
}
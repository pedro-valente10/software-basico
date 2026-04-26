#include <stdio.h>

int foo(int a[], int n);

int main(void)
{
    int a[] = {1,2,3,0,4,0};
    int n = 6;
    foo(a, n);
    for (int i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}
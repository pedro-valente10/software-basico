#include <stdio.h>
#include "header.h"

int mult(int, a int b){
int res = 0;

for (int i = 0; i<b; i++)
{
    res = soma(res, a);
}

return res;

}

int soma(int a, int b){
    return a + b;
}

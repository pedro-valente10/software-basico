#include <stdio.h>

extern int a;
extern int c;

void foo(void);

int a = 1024;
static int b = 512;

void bar(void) {
    return;
}
int main (void) {
    int d = 2;
    foo();
    bar();
    printf("%d %d %d %d\n", a, b, c, d);
    
    return 0;
}
#include "temp1.h"

int b = 0xC3;

void foo (void) {
  a = -3;
}gcc -Wa,--execstack -Wall -c temp1.c
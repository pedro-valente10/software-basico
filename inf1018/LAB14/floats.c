#include <stdio.h>
#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))

#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

typedef union { 
  float f;
  unsigned int i;
} U;

float float2(float f)
{
  U u;
  u.f = f;  /* Armazena o float na union */
  unsigned int u1 = u.i;  /* Obtém a representação "manipulável" do float*/

  unsigned int sig = getsig(u1);
  unsigned int exp = getexp(u1);
  unsigned int frac = getfrac(u1);


  if (exp == 0xff || (exp == 0 && frac == 0)) {
      return f;
  }

  if (exp == 0) {
      frac = frac << 1;
  } 

  else {
      exp = exp + 1;
  }

  u.i = makefloat(sig, exp, frac);
  return u.f;
}

float int2float(int i)
{
    if (i == 0) {
        U u;
        u.i = makefloat(0, 0, 0);
        return u.f;
    }

    unsigned int sig = 0;
    unsigned int unsigned_i;

    if (i < 0) {
        sig = 1;
        unsigned_i = (unsigned int)(-i); 
    } else {
        sig = 0;
        unsigned_i = (unsigned int)i;
    }

    int pos = 31;
    while ((unsigned_i & (1U << pos)) == 0) {
        pos--;
    }

    unsigned int exp = pos + 127;

    unsigned int mask = ~(1U << pos);
    unsigned int frac = unsigned_i & mask;

    if (pos <= 23) {
        frac = frac << (23 - pos);
    } else {
        frac = frac >> (pos - 23);
    }

    U u;
    u.i = makefloat(sig, exp, frac);
    return u.f;
}

int main() {
   int i;

   printf("\n******** int2float ****************\n");
   i = 0;
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = 1;  
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = -1;  
   printf(" %d -> %10.4f\n", i, int2float(i));
   i = 0x7fffffff;  
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = -i;
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = 12345;
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = -12345;
   printf(" %d -> %+10.4f\n", i, int2float(i));
   return 0;
}
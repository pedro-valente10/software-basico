#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_START(P) ((intptr_t)(P) & ~(pagesize - 1))
#define PAGE_END(P)   (((intptr_t)(P) + pagesize - 1) & ~(pagesize - 1))

int execpage(void *ptr, size_t len) {
    const long pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) return -1;
    return mprotect((void *)PAGE_START(ptr),
                    PAGE_END((intptr_t)ptr + len) - PAGE_START(ptr),
                    PROT_READ | PROT_WRITE | PROT_EXEC);
}
#undef PAGE_START
#undef PAGE_END



typedef int (*funcp)(int x);

int add(int x) { return x + 1; }

int main() {
    unsigned char codigo[] = {
        0xe9,
        0x00, 0x00, 0x00, 0x00
    };

    execpage(codigo, sizeof(codigo));

    int32_t desloc = (int32_t)((uintptr_t)add - (uintptr_t)(codigo + 5));
    memcpy(codigo + 1, &desloc, sizeof(desloc));

    funcp f = (funcp)codigo;
    printf("Resultado: %d\n", (*f)(10));

    return 0;
}
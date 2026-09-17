/*
int dobrar_e_somar(int x, int y);

int foo(int a, int b) {
    return dobrar_e_somar(a + 10, b * 2);
}
*/

.text
.globl foo

foo:
    pushq %rbp
    movq %rsp, $rbp
    subq %x, %rsp

    movl %edi, %eax
    addl $10, %eax

    movl %esi, %edx
    imull %2, %edx

    movl %eax, %edi
    movl %edx, %esi

    call dobrar_e_somar

    popq %rbp
    ret
    
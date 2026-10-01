/*
int soma_e_dobra(int a, int b) {
    int s = a + b;
    return triplo(s);
}
*/

.text
.globl soma_e_dobra

soma_e_dobra:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl %edi, %ecx
    addl %esi, %ecx

    movl %ecx, %edi

    call triplo

    movq %rbp, %rsp
    popq %rbp
    ret
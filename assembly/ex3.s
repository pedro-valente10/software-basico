/*
int opera_triplo(int x) {
    int temp = triplo(x);
    return temp - 5;
}
*/

.text
.globl opera_triplo

opera_triplo:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    call triplo

    subl $5, %eax
    
    movq %rbp, %rsp
    popq %rbp
    ret
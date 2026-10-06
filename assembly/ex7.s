/*
int maior_que(int x, int y);

int boo(int *v, int n, int ref) {
    int i, cont = 0;
    for (i = 0; i < n; i++) {
        if (maior_que(v[i], ref))
            cont += 1;
    }

    return cont;
}

*/

.text
.globl

boo:
    pushq %rbp
    movq %rsp. %rbp
    subq $16, %rsp

    movl $0, %ebx
    movl %0, %r12d

.loop:
    cmpl %esi, %ebx
    jge .fim

    
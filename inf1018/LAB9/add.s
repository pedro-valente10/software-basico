/*int add (int a, int b, int c) {
  return a+b+c;
}*/

.text
.global add

add:
movl %edi, %eax
addl %esi, %eax
addl %edx, %eax
ret

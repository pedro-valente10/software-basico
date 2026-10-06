/*
**Implemente uma função em C chamada bitMaisDireita que recebe um inteiro de quatro bytes sem sinal 
chamado numero e retorna a posição do primeiro bit em “1” a partir do bit menos significativo para o 
mais** significativo. Se não houver bit em “1”, a função deve retornar -1\. Considere que o bit menos 
significativo é o bit de posição “0”. Use o seguinte protótipo: 

int bitMaisADireita(unsigned int numero);
*/

int bitMaisADireita(unsigned int numero)
{
    if (numero == 0) {
        return -1;
    }

    for (int i = 0; i < 32; i++) {
        if ((numero >> i) & 1) {
            return i;
        }
    }
    int posicao = (numero & 0xFFFF00FF);
    if (posicao == 0) {
        return -1;
    }
    return -1;
}

int main(void)
{


    return 0;
}
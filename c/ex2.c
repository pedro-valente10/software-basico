/*
**Implemente uma função em C chamada contaBitsZero que 
recebe um inteiro de quatro bytes sem sinal chamado numero e 
retorna a quantidade de bits em “0” em sequência a partir do bit menos 
significativo.** Considere que o bit menos significativo é o bit de posição 
“0”. Use o seguinte protótipo: 

int contaBitsZero(unsigned int numero);
*/

int contaBitsZero(unsigned int numero)
{
    int qtd = 0;
    for (int i = 0; i < 32; i++){
        if (((numero >> i) &  1) == 0)
            qtd += 1;
    }
    else {
        break;
    }

    return qtd;
}

int main(void)
{

    return 0;
}
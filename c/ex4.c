/*
Implemente uma função em C, que dado um inteiro sem sinal retorne 
um inteiro sem sinal onde a ordem dos 4 bytes do parâmetro de entrada 
foi invertida. Use o seguinte protótipo: 

unsigned int inverteOrdemBytes(unsigned int i); 

Por exemplo, se a entrada i for igual a 0x01020304 a sáıda devera ser 0x04030201.
*/

unsigned int inverteOrdemBytes(unsigned int i)
{
    for (int k =0; k < 32; k++) {
        if (i == 0) {
            i |= 1;
        }
        else{
            i &= 0;
        }
        i = i << k;
    }
    return i;
}

int main(void)
{

    return 0;
}
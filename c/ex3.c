/*
Implemente uma função em C chamada configuraBits que recebe um inteiro de um byte 
sem sinal chamado byteConf e mais dois inteiros de 4 bytes bitInicial e bitFinal. 
Estes dois últimos parâmetros contém valores entre 0 e 7 representando o bit inicial 
e o bit final que deve ser ligado (colocado em 1) da variável byteConf. Os valores dos 
outros bits devem ser mantidos. A função deverá retornar o 1o parâmetro modificado 
conforme descrito. Use o seguinte protótipo: 

unsigned char configuraBits(unsigned char byteConf, int bitInicial, int bitFinal);

Por exemplo, se a entrada byteConf for igual a 0x80 e os parâmetros bitInicial e 
bitFinal forem iguais a 1 e 3 respectivamente, a sáıda deverá ser 0x8E.
*/

unsigned char configuraBits(unsigned char byteConf, int bitInicial, int bitFinal)
{ 
    for (int i = bitInicial; i &lt;= bitFinal; i++) { 
    byteConf |= (1 &lt;&lt; i); 
    } 
return byteConf; 
}


int main(void)
{

    return 0;
}
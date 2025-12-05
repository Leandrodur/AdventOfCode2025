#include <stdio.h>
#include <string.h>

#define BUFFSIZE 200
#define CANTDIGS 12

unsigned long long aInt(char* digitos);

int main(int nargs, char* argvc[])
{
    FILE* fpointer;
    char buffer[BUFFSIZE];
    char buffDigitos[13];
    unsigned long long acumulado=0;
    unsigned char maxPosAnterior=0;

    if(nargs != 2)
    {
        printf("Uso incorrecto, uso correcto day3 <input>\n");
        return -1;
    }
    
    fpointer = fopen(argvc[1],"r");
    if(!fpointer)
    {
        printf("Error al abrir file\n");
        return -1;
    }

    while(fgets(buffer,BUFFSIZE,fpointer))
    {
        //unsigned char max1;
        //unsigned char max1pos;
        //unsigned char max2;
        

        printf("%s",buffer);
        
        /* se comenta la primera parte
        max1 = '0';
        max2 = '0';
        for(unsigned int i=0;i<strlen(buffer)-2;i++)
        {
            if(buffer[i] > max1)
            {
                max1pos = i;
                max1=buffer[i];
            }
        }
        for(unsigned int i=max1pos+1;i<strlen(buffer);i++)
        {
            if(buffer[i] > max2)
            {
                max2=buffer[i];
            }
        }
        putchar(max1);
        putchar(max2);
        putchar('\n');

        acumulado += (max1 -'0') * 10 + max2 - '0';
        */
        
        
        maxPosAnterior=-1;

        for(unsigned int i=0;i<CANTDIGS;i++)
        {
            buffDigitos[i]=buffer[++maxPosAnterior];
            for(unsigned int j=maxPosAnterior+1;j<strlen(buffer)-1-(CANTDIGS-1-i);j++)
            {
                if(buffDigitos[i]<buffer[j])
                {
                    buffDigitos[i]=buffer[j];
                    maxPosAnterior=j;
                }
            }
        }
        buffDigitos[12] = '\0';
        printf("%s\n",buffDigitos);
        acumulado += aInt(buffDigitos);


    }
    printf("El acumulado es %lld\n",acumulado);


    return 0;
}

unsigned long long aInt(char* digitos)
{
    unsigned long long mult=1;
    unsigned long long from=0;
    for(int i = strlen(digitos)-1;i>=0;i--)
    {
        from += (digitos[i] - '0') * mult;
        mult*=10;
    }
    return from;
}

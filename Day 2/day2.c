#include <stdio.h>
#include <string.h>

unsigned long aInt(char*);
int detectarPatron(unsigned long);

int main(int nargs, char* argvc[])
{
    FILE* fpointer;
    char* rangeTo;
    unsigned long long sumPatron=0;
    int ch;

    fpointer = fopen(argvc[1],"r");

    if(!fpointer)
    {
        printf("Error al abrir file\n");
        return -1;
    }   

    char buffer[200];
    int bufIndex=0;
    do 
    {
        ch = fgetc(fpointer);
        if(ch == '\n') continue;
        if(ch == ',' || ch == EOF)
        {
            buffer[bufIndex]='\0';
            printf("buffer: %s y buffer2 %s\n",buffer,rangeTo);
            bufIndex=0;

            for (unsigned long i = aInt(buffer);i<=aInt(rangeTo);i++)
            {
                if(detectarPatron(i))
                {   
                    printf("Hay patron %ld\n",i);
                    sumPatron += i;
                    printf("Suma provisoria %lld\n",sumPatron);
                    //printf("aint %ld y \n",aInt(rangeTo));
                }
            }
        }else{
            if(ch == '-') 
            {
                ch = '\0';
                rangeTo = buffer+bufIndex+1;
            }
            buffer[bufIndex]=ch;
            bufIndex++;

        }

    }while(ch != EOF);

    printf("Sumatoria de patrones = %lld\n",sumPatron);
    return 0;   
}


unsigned long aInt(char* digitos)
{

    unsigned long mult=1;
    unsigned long from=0;
    for(int i = strlen(digitos)-1;i>=0;i--)
    {
        from += (digitos[i] - '0') * mult;
        mult*=10;
    }
    return from;
}

int detectarPatron(unsigned long nro)
{
    int indice=0;

    char buffer[100];
    sprintf(buffer,"%ld",nro);

    /* Se comenta la parte 1
    if(strlen(buffer)%2)
        return 0;

    char hayPatron = 1;

    for(int i=0;i<strlen(buffer)/2;i++)
    {
        if(buffer[i] != buffer[strlen(buffer)/2+i])
        {
            hayPatron = 0;
        }
    
    */
    //day 2 part 2:

    char hayPatron = 0;

    for(int j=1;j<=strlen(buffer)/2;j++)
    {
        indice=0;
        for(int i=0;i<strlen(buffer);i++)
        {
            if(buffer[indice] == buffer[i])
            {
                hayPatron=1;
            }else{
                hayPatron=0;
                break;
            }

            indice++;
            if(indice==j) indice = 0;
        }
        if(indice) hayPatron=0;
        if(hayPatron) break;
        
    }

    return hayPatron;
}

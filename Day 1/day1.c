#include <stdio.h>
#include <string.h>

#define BUFLEN 10

int main(int nargs, char* argvc[])
{
    FILE* fpointer;
    char buffer[BUFLEN];
    int dial = 50;
    unsigned int cantLineas=0;
    int cantCeros=0;

    // para parte 2
    int cantPases = 0;


    if(nargs != 2)
    {
        printf("Uso incorrecto\nUso correcto Day1 <input>\n");
        return -1;
    }

    fpointer = fopen(argvc[1],"r");
    
    if(!fpointer)
    {
        printf("Error al abrir file\n");
        return -1;
    }
    
    while(fgets(buffer,BUFLEN,fpointer))
    {
        unsigned char mult=1;
        int movDial=0;

        for(int i = strlen(buffer)-2;i>0;--i)
        {
            movDial += (buffer[i]-'0') * mult;
            mult*=10;
        }
        
        while(movDial>100)
        {
            movDial-=100;
            cantPases++;
        }

        if(buffer[0]=='L')
        {   
            if(dial==0) cantPases--;
            dial-= movDial;
            if(dial < 0)
            {
                dial+=100;
                cantPases++;
            }

        }else{
            dial+=movDial;
            if(dial>100)
            {
                dial-=100;
                cantPases++;
            }

            if(dial==100) dial = 0;

        }
        
        if(dial==0)
        {
            cantCeros++;
        }

        mult=1;
        cantLineas++;
        movDial=0;

    }

    printf("Lineas leidas %d\nLa cantidad de ceros es %d\n", cantLineas,cantCeros);
    printf("La cantidad de pases es %d\nTOTAL %d\n",cantPases,cantPases+cantCeros);

    fclose(fpointer);

}


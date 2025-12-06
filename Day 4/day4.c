#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 300
#define TAMINICIAL 1024

unsigned int chequearLinea(char* buffer1, char* buffer2, char* buffer3, char* bufferMod);
unsigned int getLinea(char* bufferDest,char* bufferSource);

int main(int nargs, char* argvc[])
{
    FILE* fpointer;
    char  buffer[BUFFSIZE];
    char  buffer2[BUFFSIZE];
    char  buffer3[BUFFSIZE];
    char  bufferMod[BUFFSIZE];

    char* bufferAux;
    char* buffer3Aux;

    
    char finBuffer;
    unsigned char cantRolls=0;
    unsigned int cantRollsLibres=0;
    unsigned char inLoop=1;
    unsigned char ultimaLinea=0;
    unsigned char hayCambios=1;
    unsigned int cantLineas=0;
    unsigned int tamAlloc;
    unsigned int tamLectura;
    char* buffArchivo;
    unsigned int indiceArchivo=0;

    unsigned long bytesLeidos;
    unsigned long bytesTotales=0;
    unsigned long auxCantRollsLibres=0;

    if(nargs != 2)
    {
        printf("Uso incorrecto, uso correcto day4 <input>\n");
        return -1;
    }

    fpointer = fopen(argvc[1],"r");
    if(!fpointer)
    {
        printf("Error al abrir file\n");
        return -1;
    } 

    tamAlloc = TAMINICIAL;
    buffArchivo = malloc(tamAlloc); 
    tamLectura = tamAlloc;
    
    
    while((bytesLeidos = fread(buffArchivo+bytesTotales,1,tamLectura,fpointer)))
    {
        bytesTotales+=bytesLeidos;
        if(bytesLeidos == tamLectura)
        {
            tamAlloc*=2;
            buffArchivo = realloc(buffArchivo,tamAlloc);
            tamLectura=tamAlloc-bytesTotales;
        }
    }

    printf("%s",buffArchivo);



    while(hayCambios)
    {
        indiceArchivo = 0;
        indiceArchivo += getLinea(buffer2,buffArchivo);
        indiceArchivo += getLinea(buffer3,buffArchivo+indiceArchivo);

        bufferAux = NULL;
        buffer3Aux = buffer3;

        finBuffer=0;
        while(!finBuffer)
        {
            cantRollsLibres += chequearLinea(bufferAux,buffer2,buffer3Aux,bufferMod);
            printf("normal   : %s   ",buffer2);
            printf("buffermod: %s\n",bufferMod);
            strcpy(buffArchivo+indiceArchivo-strlen(buffer2)-1-strlen(buffer3)-1, bufferMod);
            strcpy(buffer,buffer2);
            strcpy(buffer2,buffer3);
            bufferAux = buffer;


            if(buffer3Aux == NULL)
            {
                finBuffer=1;
                printf("indice Arhchivo %d bytes totales %ld\n",indiceArchivo,bytesTotales);
            }else{
                indiceArchivo += getLinea(buffer3,buffArchivo+indiceArchivo);

            }
            if(indiceArchivo > bytesTotales)
            {
                buffer3Aux = NULL;
            }
        }
        if(auxCantRollsLibres != cantRollsLibres)
        {
            auxCantRollsLibres = cantRollsLibres;
        }else{
            hayCambios = 0;
        }
    }

    /*
    fgets(buffer2,BUFFSIZE,fpointer);
    fgets(buffer3,BUFFSIZE,fpointer);

    cantLineas = 1;

    do
    {
        for(unsigned int i=0;i<strlen(buffer2)-1;i++)
        {
            cantRolls = 0;
            if(buffer2[i]!='@')
                continue;

            cantRolls=0;
            if (cantLineas!=1)
            {
                if(i!=0 && buffer2[i] == buffer[i-1])
                    cantRolls++;
                if(buffer2[i] == buffer[i])
                    cantRolls++;
                if(i!=(strlen(buffer2)-1) && buffer2[i] == buffer[i+1])
                    cantRolls++;
            }
            if(i!=0 && buffer2[i] == buffer2[i-1])
                cantRolls++;
            if(i!=(strlen(buffer2)-1) && buffer2[i] == buffer2[i+1])
                cantRolls++;
            if(!ultimaLinea)
            {
                if(i!=0 && buffer2[i] == buffer3[i-1])
                    cantRolls++;
                if(buffer2[i] == buffer3[i])
                    cantRolls++;
                if(i!=(strlen(buffer2)-1) && buffer2[i] == buffer3[i+1])
                    cantRolls++;
            }
            if (cantRolls<4)
                cantRollsLibres++;
        }

        cantLineas++;
        strcpy(buffer, buffer2);
        strcpy(buffer2,buffer3);

        if(ultimaLinea)
            inLoop=0;
        if(!fgets(buffer3,BUFFSIZE,fpointer))
            ultimaLinea=1;

    }while(inLoop);
*/
    printf("Cant lineas %d cant rolls %d\n",cantLineas,cantRollsLibres);

    return 0;
}

unsigned int chequearLinea(char* buffer1, char* buffer2, char* buffer3, char* bufferMod)
{

    unsigned char cantRolls;
    unsigned int cantRollsLibres=0;
    unsigned char hayCambios=1;
    unsigned int cantLineas=0;
    unsigned char rollChar;

    for(unsigned int i=0;i<strlen(buffer2);i++)
    {
        cantRolls = 0;
        if(buffer2[i]!='@')
        {
            bufferMod[i] = buffer2[i];
            continue;
        }
        cantRolls=0;
        if (buffer1!=NULL)
        {
            if(i!=0 && buffer2[i] == buffer1[i-1])
                cantRolls++;
            if(buffer2[i] == buffer1[i])
                cantRolls++;
            if(i!=(strlen(buffer2)-1) && buffer2[i] == buffer1[i+1])
                cantRolls++;
        }
        if(i!=0 && buffer2[i] == buffer2[i-1])
            cantRolls++;
        if(i!=(strlen(buffer2)-1) && buffer2[i] == buffer2[i+1])
            cantRolls++;
        if(buffer3!=NULL)
        {
            if(i!=0 && buffer2[i] == buffer3[i-1])
                cantRolls++;
            if(buffer2[i] == buffer3[i])
                cantRolls++;
            if(i!=(strlen(buffer2)-1) && buffer2[i] == buffer3[i+1])
                cantRolls++;
        }
        if (cantRolls<4)
        {
            rollChar = 'x';
            cantRollsLibres++;
        }else
        {
            rollChar = '@';
        }
        bufferMod[i] = rollChar;
    }

    return cantRollsLibres;
}

unsigned int getLinea(char* bufferDest,char* bufferSource)
{
    unsigned int indice=0;

    while(bufferSource[indice] != '\n' && bufferSource[indice] != '\0')
    {
        bufferDest[indice] = bufferSource[indice];
        indice++;
        
    }
    bufferDest[indice] = '\0';
    return ++indice;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct persona
{
    char rut[11];
    char nombre[20];
    char apellido[20];
    int numeroEntradas;
};

typedef struct persona tPersona;

struct crearNodo()
{
    tPersona cliente;
    struct crearNodo *sig;
};

typedef struct crearNodo Nodo;

struct Lista
{
    Nodo *cabeza;
};

void leerArchivo();

void leerArchivo(){

    FILE* file = fopen("datos1.txt", "r");

    if(file == NULL){
        printf("No se pudo leer el archivo");
    }

    char str[256];

    while (fgets(str, sizeof (str), file))
    {
        printf("%s", str);
    }

    fclose(file);
}


int main (){
    leerArchivo();
}
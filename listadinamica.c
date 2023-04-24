#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct persona
{
    char rut[11];
    char nombre[20];
    char apellido[20];
    int numeroEntradas;
    struct persona *sig;
};
typedef struct persona tPersona;
typedef tPersona * Lista;

Lista nuevoNodo(char rut[11], char nombre[20], char apellido[20], int numeroEntradas){
    Lista aux;
    aux = (Lista) malloc(sizeof(tPersona));

    while (aux != NULL)
    {
        strcpy(aux->rut, rut);
        strcpy(aux->nombre, nombre);
        strcpy(aux->apellido, apellido);
        aux->numeroEntradas = numeroEntradas;
        aux->sig = NULL;
    }
    return aux;
}

Lista creaLista(){
    return NULL;
}


void recorrerLista(Lista lista){
    Lista aux;
    aux = lista;
    while(aux != NULL){
        printf("%s,%s,%s,%d", aux->rut, aux->nombre, aux->apellido, aux->numeroEntradas);
        aux->sig;
    }
}

Lista agregarNodo(Lista lista){
    Lista aux,ultimo;
    aux = lista;

    if (lista == NULL){
        lista = nuevoNodo();
    }

    else{
        while(aux != NULL){
            if(aux->sig == NULL){
                ultimo=aux;
            }
            aux = aux->sig
        }
    }
}

int main()
{
    Lista Hola = creaLista();

    return 0;
}


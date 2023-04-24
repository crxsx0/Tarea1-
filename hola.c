#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct persona
{
    char rut[11];
    char nombreApellido[40];
    int numeroEntradas;
    struct persona *sig;
};
typedef struct persona tPersona;
typedef tPersona *Lista;

Lista nuevaLista()
{
    return NULL;
}

void agregarNodo(Lista *listaPrincipal, char rut[11], char nombreApellido[40], int numeroEntradas)
{
    Lista nuevoElemento = (Lista)malloc(sizeof(tPersona));
    strcpy(nuevoElemento->rut, rut);
    strcpy(nuevoElemento->nombreApellido, nombreApellido);
    nuevoElemento->numeroEntradas = numeroEntradas;
    nuevoElemento->sig = NULL;
    if (*listaPrincipal == NULL)
    {
        *listaPrincipal = nuevoElemento;
    }
    else
    {
        Lista ultimoE = *listaPrincipal;
        while (ultimoE->sig != NULL)
        {
            ultimoE = ultimoE->sig;
        }
        ultimoE->sig = nuevoElemento;
    }
}

void imprimirLista(Lista lista)
{
    Lista temp = lista;
    while (temp != NULL)
    {
        printf("El rut es %s, el nombre es %s y el número de entradas es %d\n", temp->rut, temp->nombreApellido, temp->numeroEntradas);
        temp = temp->sig;
    }
    printf("\n");
}

Lista leerArchivo()
{
    FILE *file = fopen("datos1.txt", "r");
    if (file == NULL)
    {
        printf("No se pudo leer el archivo");
    }
    char str[256];
    char *rut, *nombre, *apellido;
    int entradas;
    Lista clientes = nuevaLista();
    while (fgets(str, sizeof(str), file))
    {
        rut = strtok(str, ",");
        nombre = strtok(NULL, ",");
        entradas = atoi(strtok(NULL, "\n"));
        agregarNodo(&clientes, rut, nombre, entradas);
    }
    fclose(file);
    return clientes;
}

void clientesOrden(Lista clientes)
{
    Lista aux = clientes;
    while (aux != NULL)
    {
        Lista temp = aux->sig;
        while (temp != NULL)
        {
            if (strcmp(aux->rut, temp->rut) == 0)
            {
                aux->numeroEntradas += temp->numeroEntradas;
                Lista eliminar = temp;
                temp = temp->sig;
                aux->sig = temp;
                free(eliminar);
            }
            else
            {
                temp = temp->sig;
            }
        }
        printf("El rut es %s, el nombre es %s y el número de entradas es %d\n", aux->rut, aux->nombreApellido, aux->numeroEntradas);
        aux = aux->sig;
    }
}

int main()
{
    Lista clientes = leerArchivo();
    clientesOrden(clientes);
    return 0;
}


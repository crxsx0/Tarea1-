#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//cree la estructura para definir las variables y nuestro puntero
struct persona
{
    char rut[11];
    char nombreApellido[40];
    int numeroEntradas;
    struct persona *sig;
};
typedef struct persona tPersona;
typedef tPersona *Lista;
//genere una lista
Lista nuevaLista()
{
    return NULL;
}
//cree la funcion agregarnodo para generar bloques con nuestros punteros asi defini algunas condicionales cuando los bloques no contengan algun elemento. y cuando hay elementos, lo revisa y pasa el sig
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
        printf("Lista estaba vacia, se le asigno un elemento:\n");
        //printf("El rut es %s, el nombre es %s y el número de entradas es %d \n", (*listaPrincipal)->rut, (*listaPrincipal)->nombreApellido, (*listaPrincipal)->numeroEntradas);
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
    //printf("Saliendo de agregarNodo\n");
}
//esta funcion muestra la lista generada para luego poder guardarlo en texto
void imprimirLista(Lista lista) {
    Lista temp = lista;
    while (temp != NULL) {
        printf("El rut es %s, el nombre es %s y el numero de entradas es %d \n", temp->rut, temp->nombreApellido, temp->numeroEntradas);
        temp = temp->sig;
    }
    printf("\n");
}
//aqui cree la funcion de leerarchivo para poder leer el archivo de entrada y obtener los datos de estos
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
//
void clientesOrden (Lista clientes){
    Lista aux, temp, cabeza;
    aux = clientes;
    while (aux !=NULL)
    {   
        cabeza = aux
        temp = aux->sig;
        
        while (temp != NULL)
        {
            if(strcmp(aux->rut,temp->rut) == 0){
                aux -> numeroEntradas = aux ->numeroEntradas + temp->numeroEntradas;
                Lista eliminar = temp;
                temp = temp -> sig;
                cabeza ->sig = temp;
                
                //printf("%s\n", eliminar->nombreApellido);
                free(eliminar);
            }
            else{
                temp = temp -> sig;
            }
        }

        printf("El rut es %s, el nombre es %s y el numero de entradas es %d \n", aux->rut, aux->nombreApellido, aux->numeroEntradas);
        aux = aux -> sig;
    }
}
// funcion main para poder ejecutar el algoritmo
int main()
{
    Lista clientes = leerArchivo();
    //imprimirLista(clientes);
    clientesOrden(clientes);
    //imprimirLista(clientes);

    return 0;
}


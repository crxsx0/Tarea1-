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

struct memoria
{
    Lista nombreLista;
    struct memoria *sig;
};
typedef struct memoria tMemoria;
typedef tMemoria *memList;

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
    FILE *file = fopen("datos2.txt", "r");
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
Lista clientesOrden (Lista clientes){
    Lista aux, temp;
    Lista listaFinal = nuevaLista();
    memList listaEliminados;
    aux = clientes;
    while (aux !=NULL)
    {   
        temp = aux->sig;
        
        while (temp != NULL)
        {
            if(strcmp(aux->rut,temp->rut) == 0){
                aux -> numeroEntradas = aux ->numeroEntradas + temp->numeroEntradas;
                Lista eliminar = temp;
                temp = temp -> sig;
                //agregarNodoEliminado(&listaEliminados, eliminar);
                strcpy(eliminar->rut, "NULL");
            }
            else{
                temp = temp -> sig;
            }
        }

        //printf("esto es lo que contiene rut: %s\n", aux->rut);
        if (strcmp(aux->rut,"NULL")){
            //printf("El rut es %s, el nombre es %s y el numero de entradas es %d \n", aux->rut, aux->nombreApellido, aux->numeroEntradas);
            agregarNodo(&listaFinal, aux->rut, aux->nombreApellido, aux->numeroEntradas);
        }
        aux = aux -> sig;
    }

    return listaFinal;
}

void asignar(Lista ordenada, Lista *asignar, Lista *espera, int * conta){
    Lista orden;
    int totalE, contador;
    totalE = 50;
    contador = 0;
    orden = ordenada;
    while (orden != NULL)
    {
        if(contador < 50){
            if(orden -> numeroEntradas <= 2){
                agregarNodo(asignar, orden ->rut, orden -> nombreApellido, orden ->numeroEntradas);
                contador =  contador + orden->numeroEntradas;
            }

            if(orden -> numeroEntradas >= 3 && orden -> numeroEntradas <=5){
                orden -> numeroEntradas = 2;
                agregarNodo(asignar, orden ->rut, orden -> nombreApellido, orden ->numeroEntradas);
                contador =  contador + orden->numeroEntradas;
            }
        }
        
        if(contador == 50){
            contador++;
            orden = orden -> sig;
        }

        if (contador > 50){
            if(orden -> numeroEntradas <= 2){
                agregarNodo(espera, orden ->rut, orden -> nombreApellido, orden ->numeroEntradas);
            }
            if(orden -> numeroEntradas >= 3 && orden -> numeroEntradas <=5){
                orden -> numeroEntradas = 2;
                agregarNodo(espera, orden ->rut, orden -> nombreApellido, orden ->numeroEntradas);
            }
        }
        orden = orden -> sig;
    }

    if (contador == 51){
        contador = contador -1;
    }

    * conta = contador;
}

void archivoAsignacion (Lista asignacion, int contador){
    FILE *archivo = fopen("mi_archivo.txt", "w"); // Abrir el archivo en modo escritura

    if (archivo == NULL) {
        printf("Error al crear el archivo\n");
         // Salir del programa con un código de error
    }

    while (asignacion != NULL){
        fprintf(archivo, "%s,%s,%i\n", asignacion -> rut, asignacion -> nombreApellido, asignacion ->numeroEntradas);
        asignacion = asignacion -> sig;
    }

    fprintf(archivo,"Asignadas: %i\nPendientes: %i\n", contador, 50-contador);
    // Cerrar el archivo
    fclose(archivo);
}

void archivoEspera (Lista espera){
    if (espera != NULL){
        FILE *archivo = fopen("espera.txt", "w"); // Abrir el archivo en modo escritura

    if (archivo == NULL) {
        printf("Error al crear el archivo\n");
         // Salir del programa con un código de error
    }

    while (espera != NULL){
        fprintf(archivo, "%s,%s\n", espera -> rut, espera -> nombreApellido);
        espera = espera -> sig;
    }
    fclose(archivo);
    }
}
// funcion main para poder ejecutar el algoritmo
void nombreArchivo(){
    
}
int main()
{
    Lista clientes, ordenado, espera, asignacion;
    clientes = leerArchivo();
    ordenado = clientesOrden(clientes);
    espera = nuevaLista();
    asignacion = nuevaLista();
    int contador = 0;
    asignar(ordenado, &asignacion, &espera, &contador);
    archivoAsignacion(asignacion, contador);
    archivoEspera(espera);
    return 0;
}


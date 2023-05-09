#include<stdio.h>
#include<stdlib.h>

#include "linkedlist.h"

void insertarEnt(ListEnt *list, int info){
    NodoEnt *new_node = (NodoEnt *)malloc(sizeof(NodoEnt));
    new_node->info = info;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        NodoEnt *aux = list->head;
        list->head  = new_node;
        list->head->next = aux;
    }
}

void insertarChar(ListChar *list, char c){
    NodoChar *new_node = (NodoChar *)malloc(sizeof(NodoChar));
    new_node->info = c;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        NodoChar *aux = list->head;
        list->head  = new_node;
        list->head->next = aux;
    }
}


void insertarArr(ListOfArraysEnt *list, ArregloEnt info){
    NodoArr *new_node = (NodoArr *)malloc(sizeof(NodoArr));
    new_node->arreglo = info;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        NodoArr *aux = list->head;
        list->head  = new_node;
        list->head->next = aux;
    }
}

ArregloEnt listEntToArray(ListEnt *list){
    NodoEnt *aux = list->head;
    ArregloEnt array;
    array.cant = 0;
    if(aux == NULL){
        return array;
    } else {
        int i = 0;
        while( aux != NULL){
            array.arreglo[i] = aux->info;
            array.cant++;
            aux = aux->next;
            i++;
        }
        return array;
    }
}

ListEnt ArrayToListEnt(ArregloEnt arreglo){
    ListEnt result;
    for(int i = 0; i < arreglo.cant; i++){
        insertarEnt(&result, arreglo.arreglo[i]);
    }
    return result;
}

ArregloChar listCharToArray(ListChar *list){
    NodoChar *aux = list->head;
    ArregloChar array;
    array.cant = 0;
    if(aux == NULL){
        return array;
    } else {
        int i = 0;
        while( aux != NULL){
            array.arreglo[i] = aux->info;
            array.cant++;
            aux = aux->next;
            i++;
        }
        return array;
    }
}

int contenidoEstricto(ListEnt A, ListEnt B){
    ArregloEnt arrA = listEntToArray(&A);
    ArregloEnt arrB = listEntToArray(&B);

    for(int i = 0; i < arrA.cant; i++){
        int esta = 0;
        for(int j = 0; j < arrB.cant; j++){
            if( arrA.arreglo[i] == arrB.arreglo[j]){
                esta = 1;
                break;
            }
        }
        if (esta == 0){
            return 0;
        }
    }
    return 1;
}
/*
int sizeListOfArraysEnt(ListOfArraysEnt list){
    NodoArr *aux = list.head;
    int cant = 0;
    if(aux == NULL){
        return 0;
    } else {
        while( aux != NULL){
            cant++;
            aux = aux->next;
        }
        return cant;
    }
}
*/

/*
void crear(Nodo **list){
    //Inicio
    *list=NULL;
}

void insertarCab(Nodo **list, int info){
    //Lexico local
    Nodo *aux;
    //Inicio
    aux=(Nodo*) malloc(sizeof(Nodo));
    if(aux==NULL){
        printf("No hay memoria disponible!/n");
    }else{
        aux->info=info;
        aux->next=*list;
        *list=aux;
    }
}
int esVacia(Nodo *list){
    //Inicio
    if(list==NULL){
        return 1;
    }else{
        return 0;
    }
}
void suprimirCab(Nodo **list){
    //Lexico Local
    Nodo *aux;
    //Inicio
    if((esVacia(*list))==0){
        aux=*list;
        *list= (*list)->next;
        free(aux);
    }else{
        printf("La lista esta vacia!\n");
    }
}
void listar(Nodo *list){
    //Lexico Local
    Nodo *aux;
    int i;
    //Inicio
    aux=list;
    i=1;
    if(aux == NULL){
        printf("La lista esta vacia!\n");
    }
    while(aux != NULL){
        printf("\n      %i\n",i);
        printf("%i\n",aux->info);
        i++;
        aux= aux->next;
    }
}
*/
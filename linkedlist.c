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
    result.head = NULL;
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
    //aca
}

int contenido(ListEnt A, ListEnt B){
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

int incluye(ListEnt A, ListEnt B){
    ArregloEnt arrA = listEntToArray(&A);
    ArregloEnt arrB = listEntToArray(&B);

    for(int i = 0; i < arrA.cant; i++){
        for(int j = 0; j < arrB.cant; j++){
            if( arrA.arreglo[i] == arrB.arreglo[j]){
                return 1;
            }
        }
    }
    return 0;
}

int esRepetido(ListEnt A, int elem){
    ArregloEnt arrA = listEntToArray(&A);
    int bool = 0;
    for(int i = 0; i < arrA.cant; i++){
        if(arrA.arreglo[i] == elem){
            bool = 1;
        }
    }
    return bool;
}

void freeListEnt(ListEnt A){
    NodoEnt *puntero = A.head;
    while(puntero != NULL){
        NodoEnt *siguiente = puntero->next;
        free(puntero);
        puntero = siguiente;
    }
}

void freeListChar(ListChar A){
    NodoChar *puntero = A.head;
    while(puntero != NULL){
        NodoChar *siguiente = puntero->next;
        free(puntero);
        puntero = siguiente;
    }
}

void freeListOfArraysEnt(ListOfArraysEnt A){
    NodoArr *puntero = A.head;
    while(puntero != NULL){
        NodoArr *siguiente = puntero->next;
        free(puntero);
        puntero = siguiente;
    }
}
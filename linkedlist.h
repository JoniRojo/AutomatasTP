#ifndef TP_LINKEDLIST_H
#define TP_LINKEDLIST_H

#include "arreglo.h"

typedef struct NodoEnt{
    int info;
    struct NodoEnt *next;
} NodoEnt;

typedef struct NodoChar{
    char info;
    struct NodoChar *next;
} NodoChar;

typedef struct ListEnt{
    NodoEnt *head;
} ListEnt;

typedef struct ListChar{
    NodoChar *head;
} ListChar;

ArregloEnt listEntToArray(ListEnt *list);
ArregloChar listCharToArray(ListChar *list);
void insertarEnt(ListEnt *list, int info);
void insertarChar(ListChar *list, char info);
/*
void crear(Nodo **list);
void insertarCab(Nodo **list, int info);
int esVacia(Nodo *list);
void suprimirCab(Nodo **list);
void listar(Nodo *list);
*/
#endif //TP_LINKEDLIST_H
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

typedef struct NodoArr{
    ArregloEnt arreglo;
    struct NodoArr *next;
} NodoArr;

typedef struct ListEnt{
    NodoEnt *head;
} ListEnt;

typedef struct ListChar{
    NodoChar *head;
} ListChar;

typedef struct ListOfArraysEnt{
    NodoArr *head;
} ListOfArraysEnt;

ArregloEnt listEntToArray(ListEnt *list);
ArregloChar listCharToArray(ListChar *list);
ListEnt ArrayToListEnt(ArregloEnt arreglo);
void insertarEnt(ListEnt *list, int info);
void insertarChar(ListChar *list, char info);
void insertarArr(ListOfArraysEnt *list, ArregloEnt info);
int contenido(ListEnt A, ListEnt B);
int incluye(ListEnt A, ListEnt B);
int esRepetido(ListEnt A, int elem);
void freeListEnt(ListEnt A);
void freeListChar(ListChar A);
void freeListOfArraysEnt(ListOfArraysEnt A);

#endif //TP_LINKEDLIST_H

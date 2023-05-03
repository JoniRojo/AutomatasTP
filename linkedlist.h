#ifndef TP_LINKEDLIST_H
#define TP_LINKEDLIST_H

typedef struct Nodo{
    int info;
    struct Nodo *next;
} Nodo;

typedef struct List{
    Nodo *head;
} List;

//Nodo *q;

void crear(Nodo **list);
void insertarCab(Nodo **list, int info);
int esVacia(Nodo *list);
void suprimirCab(Nodo **list);
void listar(Nodo *list);
#endif //TP_LINKEDLIST_H

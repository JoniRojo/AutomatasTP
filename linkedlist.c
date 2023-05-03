#include<stdio.h>
#include<stdlib.h>

#include "linkedlist.h"

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
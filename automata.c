#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"

Automata crearAutomata(int cantSimbolos, char simbolos[],int cantEstados, int estados[], int estadoInicial, int cantFinales, const int finales[]){
    Automata aut;
    aut.cantSimbolos = cantSimbolos;
    for(int i = 0; i < cantSimbolos; i++){
        aut.simbolos[i] = simbolos[i];
    }
    aut.cantEstados = cantEstados;
    for(int j = 0; j < cantEstados; j++){
        aut.estados[j] = estados[j];
    }
    aut.estadoInicial = estadoInicial;
    aut.cantFinales = cantFinales;
    for(int k = 0; k < cantFinales; k++){
        aut.finales[k] = finales[k];
    }

    for(int a = 0 ; a < cantEstados; a++){
        for(int b = 0 ; b < cantSimbolos; b++){
            aut.delta[a][b].head = NULL;
        }
    }
    return aut;
}

void añadirTransicion(Automata *aut, int estadoDesde, char simboloPor, int estadoHacia) {
    Nodo *new_node = (Nodo *)malloc(sizeof(Nodo));
    new_node->info = estadoHacia;
    new_node->next = NULL;

    int i = indiceEstado(*aut, estadoDesde);
    int j = indiceSimbolo(*aut, simboloPor);

    if (aut->delta[i][j].head == NULL) {
        aut->delta[i][j].head  = new_node;
    } else {
        Nodo *aux = aut->delta[i][j].head;
        aut->delta[i][j].head  = new_node;
        aut->delta[i][j].head->next = aux;
    }
}

int indiceEstado(Automata aut, int estado){
    for(int i = 0; i < aut.cantEstados; i++){
        if(aut.estados[i] == estado){
            return i;
        }
    }
    return -1;
}

int indiceSimbolo(Automata aut, char simbolo){
    for(int i = 0; i < aut.cantSimbolos; i++){
        if(aut.simbolos[i] == simbolo){
            return i;
        }
    }
    return -1;
}

void mostrarAutomata(Automata aut){
    printf("Su alfabeto es: [");
    for(int j = 0; j < aut.cantSimbolos; j++){
        printf("%c ",aut.simbolos[j]);
    }
    printf("] \n");

    printf("Sus estados son: [");
    for(int j = 0; j < aut.cantEstados; j++){
        printf("%d ",aut.estados[j]);
    }
    printf("] \n");

    printf("Su estado inicial es: %d \n", aut.estadoInicial);

    printf("Sus estados finales son: [");
    for (int j = 0; j < aut.cantFinales; j++){
        printf("%d", aut.finales[j]);
    }
    printf("] \n");

    printf("Transiciones: \n");
    for (int i = 0; i < aut.cantEstados; i++) {
        for (int j = 0; j < aut.cantSimbolos; j++) {
            printf("[%d][%c]: ", aut.estados[i], aut.simbolos[j]);
            Nodo *aux = aut.delta[i][j].head;
            if(aux == NULL){
                printf("Lista vacia\n");
            }else{
                while(aux != NULL){
                    printf("%i ",aux->info);
                    aux= aux->next;
                }
                printf("\n");
            }
        }
    }
}
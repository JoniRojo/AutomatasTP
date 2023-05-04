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

void pertenece(Automata aut, char cadena[], int n){
    int indiceEstadoInicial = indiceEstado(aut, aut.estadoInicial);
    int indicePrimerSimbolo = indiceSimbolo(aut, cadena[0]);
    int aceptada = 0;
    if (aut.delta[indiceEstadoInicial][indicePrimerSimbolo].head != NULL){          //si desde el estado inicial por el primer simbolo voy a algun estado
        int aux = aut.delta[indiceEstadoInicial][indicePrimerSimbolo].head->info;   //aux es un estado
        for (int i = 1; i < n; i++){
            aux = ir(aut, aux, cadena[i]);                                          //consumo toda la cadena
        }
        for (int j = 0; j < aut.cantFinales; j++){
            if (aux == aut.finales[j]){                                             //chequeo si llegue a un estado final
                aceptada = 1;
            }
        }
    }
    if(aceptada == 1){
        printf("Cadena aceptada por el automata");
    }else{
        printf("Cadena no aceptada por el automata");
    }
}

int ir(Automata aut, int aux, char c){
    int indiceAux = indiceEstado(aut, aux);
    int indiceSim = indiceSimbolo(aut, c);
    return aut.delta[indiceAux][indiceSim].head->info;
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
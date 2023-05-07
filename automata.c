#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"

Automata crearAutomata(ArregloChar simbolos, ArregloEnt estados, int estadoInicial, ArregloEnt finales){
    Automata aut;
    for(int i = 0; i < simbolos.cant; i++){
        aut.simbolos.arreglo[i] = simbolos.arreglo[i];
    }
    aut.simbolos.cant = simbolos.cant;
    aut.estados.cant = estados.cant;
    for(int j = 0; j < estados.cant; j++){
        aut.estados.arreglo[j] = estados.arreglo[j];
    }
    aut.estadoInicial = estadoInicial;
    aut.finales.cant = finales.cant;
    for(int k = 0; k < finales.cant; k++){
        aut.finales.arreglo[k] = finales.arreglo[k];
    }

    for(int a = 0 ; a < estados.cant; a++){
        for(int b = 0 ; b < simbolos.cant; b++){
            aut.delta[a][b].head = NULL;
        }
    }
    return aut;
}

void añadirTransicion(Automata *aut, int estadoDesde, char simboloPor, int estadoHacia) {
    NodoEnt *new_node = (NodoEnt *)malloc(sizeof(NodoEnt));
    new_node->info = estadoHacia;
    new_node->next = NULL;

    int i = indiceEstado(*aut, estadoDesde);
    int j = indiceSimbolo(*aut, simboloPor);

    if (aut->delta[i][j].head == NULL) {
        aut->delta[i][j].head  = new_node;
    } else {
        NodoEnt *aux = aut->delta[i][j].head;
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
        for (int i = 1; i < n ; i++){
            aux = ir(aut, aux, cadena[i]);                                          //consumo toda la cadena
        }
        for (int j = 0; j < aut.finales.cant; j++){
            if (aux == aut.finales.arreglo[j]){                                             //chequeo si llegue a un estado final
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

Automata AFNDtoAFD(Automata aut){
    //Implementar
}

ListEnt clausuraLambda(Automata aut, ArregloEnt estados){
    // recorrer todos los estados de ArregloEnt estados
    // por cada estado recorrer la lista en la matriz[estado[i]][z]
    // por lo que me da, lo agrego a la lista resultado
    int indiceLambda = indiceSimbolo(aut, 'z');
    ListEnt result;
    result.head = NULL;

    for(int i = 0; i < estados.cant; i++){
        int indiceEst = indiceEstado(aut, estados.arreglo[i]);
        NodoEnt *aux = aut.delta[indiceEst][indiceLambda].head;
        if(aux == NULL){
            break;
        } else {
            while( aux != NULL){
                NodoEnt *new_node = (NodoEnt *)malloc(sizeof(NodoEnt));
                new_node->info = aux->info;
                new_node->next = NULL;

                if (result.head == NULL) {
                    result.head  = new_node;
                } else {
                    NodoEnt *aux2 = result.head;
                    result.head = new_node;
                    result.head->next = aux2;
                }
                aux = aux->next;
            }
        }
    }
    ArregloEnt resultArray = listEntToArray(&result);
    for(int j = 0; j < estados.cant; j++){
        int esta = 0;
        for(int k = 0; k < resultArray.cant; k++){
            if(estados.arreglo[j] == resultArray.arreglo[k]){
                esta = 1;
            }
        }
        if(esta == 1){
            insertarEnt(&result,estados.arreglo[j]);
        }
    }
    return result;
}

ListEnt mover(Automata aut, ArregloEnt estados, char simbolo){
    int indiceSimb = indiceSimbolo(aut, simbolo);
    ListEnt result;
    result.head = NULL;

    for(int i = 0; i < estados.cant; i++){
        int indiceEst = indiceEstado(aut, estados.arreglo[i]);
        NodoEnt *aux = aut.delta[indiceEst][indiceSimb].head;
        if(aux == NULL){
            break;
        } else {
            while( aux != NULL){
                NodoEnt *new_node = (NodoEnt *)malloc(sizeof(NodoEnt));
                new_node->info = aux->info;
                new_node->next = NULL;

                if (result.head == NULL) {
                    result.head  = new_node;
                } else {
                    NodoEnt *aux2 = result.head;
                    result.head = new_node;
                    result.head->next = aux2;
                }
                aux = aux->next;
            }
        }
    }
    return result;
}

int indiceEstado(Automata aut, int estado){
    for(int i = 0; i < aut.estados.cant; i++){
        if(aut.estados.arreglo[i] == estado){
            return i;
        }
    }
    return -1;
}

int indiceSimbolo(Automata aut, char simbolo){
    for(int i = 0; i < aut.simbolos.cant; i++){
        if(aut.simbolos.arreglo[i] == simbolo){
            return i;
        }
    }
    return -1;
}

void mostrarAutomata(Automata aut){
    printf("Su alfabeto es: [");
    for(int j = 0; j < aut.simbolos.cant; j++){
        printf("%c ",aut.simbolos.arreglo[j]);
    }
    printf("] \n");

    printf("Sus estados son: [");
    for(int j = 0; j < aut.estados.cant; j++){
        printf("%d ",aut.estados.arreglo[j]);
    }
    printf("] \n");

    printf("Su estado inicial es: %d \n", aut.estadoInicial);

    printf("Sus estados finales son: [");
    for (int j = 0; j < aut.finales.cant; j++){
        printf("%d", aut.finales.arreglo[j]);
    }
    printf("] \n");

    printf("Transiciones: \n");
    for (int i = 0; i < aut.estados.cant; i++) {
        for (int j = 0; j < aut.simbolos.cant; j++) {
            printf("[%d][%c]: ", aut.estados.arreglo[i], aut.simbolos.arreglo[j]);
            NodoEnt *aux = aut.delta[i][j].head;
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
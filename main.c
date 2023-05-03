#include <stdio.h>
#include <malloc.h>

#include "automata.h"

int main(){
    int cantidadSimbolos = 3;
    char alfabeto[] = {'z', 'a', 'b'};
    int cantidadEstados = 3;
    int estados[] = {1, 2, 3};
    int inicial = 1;
    int cantidadFinales = 1;
    int finales[] = {3};

    Automata a = crearAutomata(cantidadSimbolos, alfabeto, cantidadEstados, estados, inicial, cantidadFinales, finales);

    añadirTransicion(&a,1,'z',2);
    añadirTransicion(&a,1,'a',1);
    añadirTransicion(&a,1,'b',3);
    añadirTransicion(&a, 2, 'a', 2);
    añadirTransicion(&a, 2,'a',3);
    añadirTransicion(&a, 3, 'b', 2);

    mostrarAutomata(a);
    /*
    Matriz delta;
    delta.estados = cantidadEstados;
    delta.simbolos = cantidadSimbolos;
    delta.matriz = (int***) malloc(sizeof(int**) * delta.estados);

    for (int i = 0; i < delta.estados; i++) {
        delta.matriz[i] = (int**) malloc(sizeof(int*) * delta.simbolos);
        for (int j = 0; j < delta.simbolos; j++) {
            delta.matriz[i][j] = (int*) malloc(sizeof(int));
            delta.matriz[i][j][0] = '\0';
        }
    }

    inicializarMatriz(delta, cantidadEstados, cantidadSimbolos);

    llenarMatriz(a,0,1,'z',2);
    llenarMatriz(a,0,1,'a',1);
    llenarMatriz(a,0,1,'b',3);
    llenarMatriz(a,0,2,'z',-1);
    llenarMatriz(a,0,2,'a',2);
    llenarMatriz(a,1,2,'a',3);
    llenarMatriz(a,0,2,'b',-1);
    llenarMatriz(a,0,3,'z',-1);
    llenarMatriz(a,0,3,'a',-1);
    llenarMatriz(a,0,3,'z',2);
    */
}
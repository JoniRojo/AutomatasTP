#ifndef TP_AUTOMATA_H
#define TP_AUTOMATA_H
#define MAX 500

#include "linkedlist.h"

/*
typedef struct Matriz{
    int estados;    //filas
    int simbolos;   //columnas
    int*** matriz;
}Matriz;
*/

typedef struct Automata{
    int cantSimbolos; // Cantidad de simbolos del alfabeto
    int cantEstados;  // Cantidad de estados
    int cantFinales;  // Cantidad de estados finales
    int estados[MAX];     // Los estados son numeros
    char simbolos[MAX];   // Los simbolos del alfabeto son caracteres
    List delta[MAX][MAX];
    int finales[MAX];     // Conjunto de estados finales
    int estadoInicial;    // Estado inicial
}Automata;

/*
typedef struct Matriz{
    int cantEstados;
    int cantSimbolos;
    //int estadoDesde;
    //char porSimbolo;
    List *lista;
}Matriz;
*/

Automata crearAutomata(int cantSimbolos, char simbolos[],int cantEstados, int estados[], int estadoInicial, int cantFinales, const int finales[]);

//Matriz crearMatriz(int cantEstados, int cantSimbolos);
void añadirTransicion(Automata *aut, int estadoDesde, char simboloPor, int estadoHacia );

int indiceEstado(Automata aut, int estado);
int indiceSimbolo(Automata aut, char simbolo);
/*
void inicializarMatriz(List delta, int cantEstados, int cantSimbolos);

void llenarMatriz(Automata aut, int k, int desde, char por, int hacia);
*/
void mostrarAutomata(Automata aut);

#endif //TP_AUTOMATA_H

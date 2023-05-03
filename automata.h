#ifndef TP_AUTOMATA_H
#define TP_AUTOMATA_H
#define MAX 500

#include "linkedlist.h"

typedef struct Automata{
    int cantSimbolos; 
    int cantEstados;
    int cantFinales;
    int estados[MAX];       // Estados son numeros
    char simbolos[MAX];     // Simbolos del alfabeto son caracteres
    List delta[MAX][MAX];   // Filas son estados, columnas son simbolos, cada elemento de la matriz es una lista
    int finales[MAX];
    int estadoInicial;
}Automata;

Automata crearAutomata(int cantSimbolos, char simbolos[],int cantEstados, int estados[], int estadoInicial, int cantFinales, const int finales[]);

void añadirTransicion(Automata *aut, int estadoDesde, char simboloPor, int estadoHacia );

int indiceEstado(Automata aut, int estado);

int indiceSimbolo(Automata aut, char simbolo);

void mostrarAutomata(Automata aut);

#endif //TP_AUTOMATA_H
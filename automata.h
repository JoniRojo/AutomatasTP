#ifndef TP_AUTOMATA_H
#define TP_AUTOMATA_H
#define MAX 50

#include "linkedlist.h"
#include "arreglo.h"

typedef struct Automata{
    ArregloEnt estados;       // Estados son numeros
    ArregloChar simbolos;     // Simbolos del alfabeto son caracteres
    ListEnt delta[MAX][MAX];   // Filas son estados, columnas son simbolos, cada elemento de la matriz es una lista
    ArregloEnt finales;
    int estadoInicial;
}Automata;

Automata crearAutomata(ArregloChar simbolos, ArregloEnt estados, int estadoInicial, ArregloEnt finales);

void anadirTransicion(Automata *aut, int estadoDesde, char simboloPor, int estadoHacia);

void pertenece(Automata aut, char cadena[], int n);

int ir(Automata aut, int aux, char simbolo);

Automata AFNDtoAFD(Automata aut);

void cicloNuevosConjuntos(Automata aut, Automata *nuevoAut, ListOfArraysEnt listaEstadosAIterar, ListOfArraysEnt *listaEstadosResultado, ArregloChar alfabetoSinLambda);

int nuevoNombreEstado(ArregloEnt conjuntoNuevo);

ListEnt clausuraLambda(Automata aut, ArregloEnt estados);

ListEnt mover(Automata aut, ArregloEnt estados, char simbolo);

int indiceEstado(Automata aut, int estado);

int indiceSimbolo(Automata aut, char simbolo);

Automata unionAut(Automata a, Automata b);

void estadosRepetidos(Automata *a, Automata b);

Automata concatenarAut(Automata a, Automata b);

Automata clausuraKlenneAut(Automata a);

Automata minimizacionAut(Automata a);

void refinarClasesEquivalencia();

void mostrarAutomata(Automata aut);

void freeDelta(Automata aut);

#endif //TP_AUTOMATA_H
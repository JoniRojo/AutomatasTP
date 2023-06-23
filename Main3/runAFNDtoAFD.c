#include <stdio.h>
#include <malloc.h>

#include "../automata.h"
#include "../linkedlist.h"

/*
int main(){

    // Automata ejemplo del libro
    ListChar listaAlfabeto;
    insertarChar(&listaAlfabeto, 'z');
    insertarChar(&listaAlfabeto, 'a');
    insertarChar(&listaAlfabeto, 'b');
    insertarChar(&listaAlfabeto, 'c');
    ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

    ListEnt listaEstados;
    insertarEnt(&listaEstados, 1);
    insertarEnt(&listaEstados, 2);
    insertarEnt(&listaEstados, 3);
    insertarEnt(&listaEstados, 4);
    insertarEnt(&listaEstados, 5);
    insertarEnt(&listaEstados, 6);
    ArregloEnt estados = listEntToArray(&listaEstados);

    int inicial = 1;

    ListEnt listaFinales;
    insertarEnt(&listaFinales,5);
    insertarEnt(&listaFinales,6);
    ArregloEnt finales = listEntToArray(&listaFinales);

    Automata a = crearAutomata( alfabeto, estados, inicial, finales);

    anadirTransicion(&a,1,'a',2);
    anadirTransicion(&a,1,'z',4);
    anadirTransicion(&a, 2, 'c', 3);
    anadirTransicion(&a, 3, 'z', 6);
    anadirTransicion(&a, 4, 'b', 5);
    anadirTransicion(&a, 4, 'b', 6);
    anadirTransicion(&a, 5, 'b', 5);
    anadirTransicion(&a, 5, 'b', 6);
    anadirTransicion(&a, 6, 'z', 1);

    mostrarAutomata(a);

    Automata aAFD = AFNDtoAFD(a);
    mostrarAutomata(aAFD);
    freeDelta(a);
    freeDelta(aAFD);
}
*/
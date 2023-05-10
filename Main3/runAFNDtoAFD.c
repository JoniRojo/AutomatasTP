#include <stdio.h>
#include <malloc.h>

#include "../automata.h"

int main(){
    ListChar listaAlfabeto;
    insertarChar(&listaAlfabeto, 'z');
    insertarChar(&listaAlfabeto, 'a');
    insertarChar(&listaAlfabeto, 'b');
    insertarChar(&listaAlfabeto, 'c');
    ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

    ListEnt listaEstados;
    insertarEnt(&listaEstados, 0);
    insertarEnt(&listaEstados, 1);
    insertarEnt(&listaEstados, 2);
    insertarEnt(&listaEstados, 3);
    insertarEnt(&listaEstados, 4);
    insertarEnt(&listaEstados, 5);
    ArregloEnt estados = listEntToArray(&listaEstados);

    int inicial = 1;

    ListEnt listaFinales;
    insertarEnt(&listaFinales,4);
    insertarEnt(&listaFinales,5);
    ArregloEnt finales = listEntToArray(&listaFinales);

    Automata a = crearAutomata( alfabeto, estados, inicial, finales);

    anadirTransicion(&a,0,'a',1);
    anadirTransicion(&a,0,'z',3);
    anadirTransicion(&a, 1, 'c', 2);
    anadirTransicion(&a, 2, 'z', 5);
    anadirTransicion(&a, 3, 'b', 4);
    anadirTransicion(&a, 3, 'b', 5);
    anadirTransicion(&a, 4, 'b', 4);
    anadirTransicion(&a, 4, 'b', 5);
    anadirTransicion(&a, 5, 'z', 0);

    mostrarAutomata(a);

    Automata aAFD = AFNDtoAFD(a);
    mostrarAutomata(aAFD);
}
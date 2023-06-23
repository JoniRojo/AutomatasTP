#include <stdio.h>
#include <malloc.h>

#include "../automata.h"
/*
int main(){
    // Ejemplo del libro

    ListChar listaAlfabeto;
    insertarChar(&listaAlfabeto, 'z');
    insertarChar(&listaAlfabeto, 'a');
    ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

    ListEnt listaEstados;
    insertarEnt(&listaEstados, 1);
    insertarEnt(&listaEstados, 2);
    ArregloEnt estados = listEntToArray(&listaEstados);

    int inicial = 1;

    ListEnt listaFinales;
    insertarEnt(&listaFinales,2);
    ArregloEnt finales = listEntToArray(&listaFinales);

    Automata a = crearAutomata( alfabeto, estados, inicial, finales);

    anadirTransicion(&a,1,'a',2);
    anadirTransicion(&a,2,'a',2);

    printf("Primer automata: \n");
    mostrarAutomata(a);

    printf("----------------------------------------------------------------------\n");
    Automata nuevoAutomataClausuraKlenne = clausuraKlenneAut(a);
    printf("Clausura de Klenne del automata a: \n");
    mostrarAutomata(nuevoAutomataClausuraKlenne);
}
*/

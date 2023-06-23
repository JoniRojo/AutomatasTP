#include <stdio.h>
#include <malloc.h>

#include "../automata.h"
/*
int main(){
    // Ejemplo del libro

    ListChar listaAlfabeto;
    insertarChar(&listaAlfabeto, 'z');
    insertarChar(&listaAlfabeto, 'a');
    insertarChar(&listaAlfabeto, 'b');
    ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

    ListEnt listaEstados;
    insertarEnt(&listaEstados, 1);
    insertarEnt(&listaEstados, 2);
    insertarEnt(&listaEstados, 3);
    insertarEnt(&listaEstados, 4);
    insertarEnt(&listaEstados, 5);
    ArregloEnt estados = listEntToArray(&listaEstados);

    int inicial = 1;

    ListEnt listaFinales;
    insertarEnt(&listaFinales,3);
    insertarEnt(&listaFinales,4);
    ArregloEnt finales = listEntToArray(&listaFinales);

    Automata a = crearAutomata( alfabeto, estados, inicial, finales);

    // 0 = a, 1 = b
    anadirTransicion(&a,1,'a',2);
    anadirTransicion(&a,1,'b',5);
    anadirTransicion(&a,2,'a',5);
    anadirTransicion(&a,2,'b',3);
    anadirTransicion(&a,3,'a',5);
    anadirTransicion(&a,3,'b',4);
    anadirTransicion(&a,4,'a',5);
    anadirTransicion(&a,4,'b',3);
    anadirTransicion(&a,5,'a',5);
    anadirTransicion(&a,5,'b',5);

    printf("Primer automata: \n");
    mostrarAutomata(a);

    printf("----------------------------------------------------------------------\n");
    Automata nuevoAutomataMinimizado = minimizacionAut(a);
    // 1 = a, 0 = b
    printf("Minimizacion del automata: \n");
    mostrarAutomata(nuevoAutomataMinimizado);
}
*/
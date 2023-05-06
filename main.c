#include <stdio.h>
#include <malloc.h>

#include "automata.h"

int main(){
    ListChar listaAlfabeto;
    insertarChar(&listaAlfabeto, 'z');
    insertarChar(&listaAlfabeto, 'a');
    insertarChar(&listaAlfabeto, 'b');
    ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

    ListEnt listaEstados;
    insertarEnt(&listaEstados, 1);
    insertarEnt(&listaEstados, 2);
    insertarEnt(&listaEstados, 3);
    ArregloEnt estados = listEntToArray(&listaEstados);

    int inicial = 1;

    ListEnt listaFinales;
    insertarEnt(&listaFinales,3);
    ArregloEnt finales = listEntToArray(&listaFinales);

    Automata a = crearAutomata( alfabeto, estados, inicial, finales);

    /* Ejemplo AF 1
    añadirTransicion(&a,1,'z',2);
    añadirTransicion(&a,1,'a',1);
    añadirTransicion(&a,1,'b',3);
    añadirTransicion(&a, 2, 'a', 2);
    añadirTransicion(&a, 2,'a',3);
    añadirTransicion(&a, 3, 'b', 2);
    */

    // Ejemplo AF 2
    añadirTransicion(&a,1,'a',1);
    añadirTransicion(&a,1,'b',3);
    añadirTransicion(&a, 2, 'a', 3);
    añadirTransicion(&a, 3, 'b', 2);

    mostrarAutomata(a);

    // Aceptada
    /*
    char cadena[] = {'a','b', 'b', 'a'};
    int n = 4;
     */
    // No aceptada
    char cadena[] = {'a','b', 'b'};
    int n = 3;
    pertenece(a, cadena, n);
}
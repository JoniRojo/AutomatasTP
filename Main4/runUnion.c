#include <stdio.h>
#include <malloc.h>

#include "../automata.h"

/*
int main(){
    // Ejemplo del libro

    ListChar listaAlfabeto1;
    insertarChar(&listaAlfabeto1, 'z');
    insertarChar(&listaAlfabeto1, 'a');
    ArregloChar alfabeto1 = listCharToArray(&listaAlfabeto1);

    ListEnt listaEstados1;
    insertarEnt(&listaEstados1, 1);
    insertarEnt(&listaEstados1, 3);
    ArregloEnt estados1 = listEntToArray(&listaEstados1);

    int inicial1 = 1;

    ListEnt listaFinales1;
    insertarEnt(&listaFinales1,3);
    ArregloEnt finales1 = listEntToArray(&listaFinales1);

    Automata a1 = crearAutomata( alfabeto1, estados1, inicial1, finales1);

    anadirTransicion(&a1,1,'a',3);
    anadirTransicion(&a1,3,'a',3);

    printf("Primer automata: \n");
    mostrarAutomata(a1);

    printf("----------------------------------------------------------------------\n");
    ListChar listaAlfabeto2;
    insertarChar(&listaAlfabeto2, 'z');
    insertarChar(&listaAlfabeto2, 'a');
    insertarChar(&listaAlfabeto2, 'b');
    ArregloChar alfabeto2 = listCharToArray(&listaAlfabeto2);

    ListEnt listaEstados2;
    insertarEnt(&listaEstados2, 3);
    insertarEnt(&listaEstados2, 4);
    ArregloEnt estados2 = listEntToArray(&listaEstados2);

    int inicial2 = 3;

    ListEnt listaFinales2;
    insertarEnt(&listaFinales2,3);
    ArregloEnt finales2 = listEntToArray(&listaFinales2);

    Automata a2 = crearAutomata( alfabeto2, estados2, inicial2, finales2);

    anadirTransicion(&a2,3,'b',4);
    anadirTransicion(&a2,4,'a',3);

    printf("Segundo automata: \n");
    mostrarAutomata(a2);

    printf("----------------------------------------------------------------------\n");

    Automata nuevoAutomataUnion = unionAut(a1,a2);
    printf("Union automata a1 a2: \n");
    mostrarAutomata(nuevoAutomataUnion);
}
 */
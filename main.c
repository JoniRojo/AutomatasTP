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
}
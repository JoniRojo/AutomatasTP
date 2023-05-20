#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "linkedlist.h"

Automata crearAutomata(ArregloChar simbolos, ArregloEnt estados, int estadoInicial, ArregloEnt finales){
    Automata aut;
    for(int i = 0; i < simbolos.cant; i++){
        aut.simbolos.arreglo[i] = simbolos.arreglo[i];
    }
    aut.simbolos.cant = simbolos.cant;
    aut.estados.cant = estados.cant;
    for(int j = 0; j < estados.cant; j++){
        aut.estados.arreglo[j] = estados.arreglo[j];
    }
    aut.estadoInicial = estadoInicial;
    aut.finales.cant = finales.cant;
    for(int k = 0; k < finales.cant; k++){
        aut.finales.arreglo[k] = finales.arreglo[k];
    }

    for(int a = 0 ; a < estados.cant; a++){
        for(int b = 0 ; b < simbolos.cant; b++){
            aut.delta[a][b].head = NULL;
        }
    }
    return aut;
}

void anadirTransicion(Automata *aut, int estadoDesde, char simboloPor, int estadoHacia) {
    NodoEnt *new_node = (NodoEnt *)malloc(sizeof(NodoEnt));
    new_node->info = estadoHacia;
    new_node->next = NULL;

    int i = indiceEstado(*aut, estadoDesde);
    int j = indiceSimbolo(*aut, simboloPor);

    if (aut->delta[i][j].head == NULL) {
        aut->delta[i][j].head  = new_node;
    } else {
        NodoEnt *aux = aut->delta[i][j].head;
        aut->delta[i][j].head  = new_node;
        aut->delta[i][j].head->next = aux;
    }
}

void pertenece(Automata aut, char cadena[], int n){
    int indiceEstadoInicial = indiceEstado(aut, aut.estadoInicial);
    int indicePrimerSimbolo = indiceSimbolo(aut, cadena[0]);
    int aceptada = 0;
    if (aut.delta[indiceEstadoInicial][indicePrimerSimbolo].head != NULL){  //si desde el estado inicial por el primer simbolo voy a algun estado
        int aux = aut.delta[indiceEstadoInicial][indicePrimerSimbolo].head->info;  //aux es un estado
        for (int i = 1; i < n ; i++){
            aux = ir(aut, aux, cadena[i]);  //consumo toda la cadena
        }
        for (int j = 0; j < aut.finales.cant; j++){
            if (aux == aut.finales.arreglo[j]){  // chequeo si llegue a un estado final
                aceptada = 1;
            }
        }
    }
    if(aceptada == 1){
        printf("Cadena aceptada por el automata");
    }else{
        printf("Cadena no aceptada por el automata");
    }
}

int ir(Automata aut, int aux, char c){
    int indiceAux = indiceEstado(aut, aux);
    int indiceSim = indiceSimbolo(aut, c);
    return aut.delta[indiceAux][indiceSim].head->info;
}

Automata AFNDtoAFD(Automata aut){
    Automata nuevoAut;
    nuevoAut.simbolos = aut.simbolos;

    // dado que clasuraLambda toma un arreglo de estados, pasamos nuestro estado inicial(int) a un ArregloEnt
    ArregloEnt estadoIncialArr;
    estadoIncialArr.arreglo[0] = aut.estadoInicial;
    estadoIncialArr.cant = 1;
    ListEnt clausuraLambdaEstadoInicialL = clausuraLambda(aut, estadoIncialArr);
    ArregloEnt clausuraLambdaEstadoInicialA = listEntToArray(&clausuraLambdaEstadoInicialL);

    int nuevoInicial = nuevoNombreEstado(clausuraLambdaEstadoInicialA);
    nuevoAut.estadoInicial = nuevoInicial;

    // actualizo mi arreglo de estados en el nuevo automata
    nuevoAut.estados.arreglo[nuevoAut.estados.cant] = nuevoInicial;
    nuevoAut.estados.cant = nuevoAut.estados.cant + 1;

    // creo una lista de listas de arreglos, donde cada nodo sera un arreglo de estados,
    //  que luego unificare para formar un solo estado para el AFD(nuevoNombre)
    // a esta lista le agrego inicialmente la clausura lambda del estado inicial

    ListOfArraysEnt listaEstadosNuevos;
    insertarArr(&listaEstadosNuevos, clausuraLambdaEstadoInicialA);

    // en este for obtenemos nuestros primeros conjuntos producto de calcular mover por cada simbolo y al conjunto resultado, su clausura lambda
    // pero primero debemos obtener el alfabeto sin el lambda para iterar en el metodo mover

    ListChar alfabetoSinLambdaL;
    for(int k = 0; k < aut.simbolos.cant; k++){
        if(aut.simbolos.arreglo[k] != 'z'){
            insertarChar(&alfabetoSinLambdaL, aut.simbolos.arreglo[k]);
        }
    }
    ArregloChar alfabetoSinLambda = listCharToArray(&alfabetoSinLambdaL);

    ListOfArraysEnt listaEstadosAIterar;
    for(int i = 0; i < alfabetoSinLambda.cant; i++){
        ListEnt aux = mover(aut, clausuraLambdaEstadoInicialA, alfabetoSinLambda.arreglo[i]);
        ArregloEnt aux2 = listEntToArray(&aux);
        ListEnt conjuntoNuevo = clausuraLambda(aut, aux2);
        ArregloEnt conjuntoNuevoArr = listEntToArray(&conjuntoNuevo);

        // chequeo si alguno de estos conjuntos de estados esta contenido en mi conjunto de la clausura del estado inicial
        // si no esta contenido, lo agrego a la lista estados(del AFD) y lo guardo para procesar luego
        if(contenido(conjuntoNuevo, clausuraLambdaEstadoInicialL) == 0){
            insertarArr(&listaEstadosNuevos, conjuntoNuevoArr);
            insertarArr(&listaEstadosAIterar,conjuntoNuevoArr);
            // creo la representacion del nuevo estado
            int nuevoNum = nuevoNombreEstado(conjuntoNuevoArr);
            // actualizo mi arreglo de estados en el nuevo automata
            nuevoAut.estados.arreglo[nuevoAut.estados.cant] = nuevoNum;
            nuevoAut.estados.cant = nuevoAut.estados.cant + 1;

            // agrego transicion
            anadirTransicion(&nuevoAut,nuevoInicial, alfabetoSinLambda.arreglo[i], nuevoNum);
        }
    }

    // llamo a cicloNuevosConjuntos, metodo para ciclar buscando conjuntos nuevos
    cicloNuevosConjuntos(aut, &nuevoAut, listaEstadosAIterar, &listaEstadosNuevos, alfabetoSinLambda);

    // para este punto, ya tenemos el alfabeto, el estado inical y las transiciones...
    // definimos aquellos estados que son finales
    ListEnt nuevosAutFinales;
    NodoArr *pAListaEstados = listaEstadosNuevos.head;
    while(pAListaEstados != NULL){
        ListEnt A = ArrayToListEnt(aut.finales);
        ListEnt B = ArrayToListEnt(pAListaEstados->arreglo);
        if(incluye(A,B) == 1){
            int finalNuevo = nuevoNombreEstado(pAListaEstados->arreglo);
            insertarEnt(&nuevosAutFinales, finalNuevo);
        }
        pAListaEstados = pAListaEstados->next;
    }

    // ahora queda pasar todos los arreglos de la lista listaEstadosNuevos(ListOfArraysEnt) a su nueva representacion
    ListEnt nuevoAutEstados;
    pAListaEstados = listaEstadosNuevos.head;
    while(pAListaEstados != NULL){
        int nuevoNom = nuevoNombreEstado(pAListaEstados->arreglo);
        insertarEnt(&nuevoAutEstados,nuevoNom);
        pAListaEstados = pAListaEstados->next;
    }

    nuevoAut.estados = listEntToArray(&nuevoAutEstados);
    nuevoAut.finales = listEntToArray(&nuevosAutFinales);
    //freeListEnt(nuevosEstados);
    //freeListEnt(nuevosFinales);
    return nuevoAut;
}


// listaEstadosResultado es la lista de los estados que finalmente tendre en mi nuevo ADF
// listaEstadosAIterar es la lista utilizada para almacenar la lista de estados a iterar
void cicloNuevosConjuntos(Automata aut, Automata *nuevoAut, ListOfArraysEnt listaEstadosAIterar, ListOfArraysEnt *listaEstadosResultado, ArregloChar alfabetoSinLambda){
    NodoArr *pAlistaEstadosAIterar = listaEstadosAIterar.head;
    NodoArr *pAlistaEstadosResultado = listaEstadosResultado->head;
    ListOfArraysEnt listaEstadosNuevosAIterar;
    while( pAlistaEstadosAIterar != NULL){  // Mientras tenga conjuntos a iterar
        for(int i = 0; i < alfabetoSinLambda.cant; i++){    // por cada simbolo del alfabeto
            // calculo clausuraLambda(mover())
            ListEnt aux = mover(aut, pAlistaEstadosAIterar->arreglo, alfabetoSinLambda.arreglo[i]);
            ArregloEnt aux2 = listEntToArray(&aux);
            ListEnt conjuntoNuevo = clausuraLambda(aut, aux2);
            ArregloEnt conjuntoNuevoArr = listEntToArray(&conjuntoNuevo);
            if(conjuntoNuevoArr.cant != 0){
                int esta = 0;
                //ArregloEnt arregloAux;
                while( pAlistaEstadosResultado != NULL){  // por cada estado "ya confirmado" en mi nuevo AFD(listaEstadosResultado)
                    ListEnt conjunto = ArrayToListEnt(pAlistaEstadosResultado->arreglo);
                    // chequeo si el conjunto obtenido esta contenido en el arreglo actual de listaEstadosResultado
                    if(contenido(conjuntoNuevo, conjunto) == 1){
                        esta = 1;
                    }
                    //arregloAux = pAlista2 ->arreglo;
                    pAlistaEstadosResultado = pAlistaEstadosResultado->next;
                }
                if(esta == 0){
                    insertarArr(listaEstadosResultado, conjuntoNuevoArr);
                    insertarArr(&listaEstadosNuevosAIterar,conjuntoNuevoArr);
                    // actualizo mi arreglo de estados en el nuevo automata
                    int nuevoNum = nuevoNombreEstado(conjuntoNuevoArr);
                    nuevoAut->estados.arreglo[nuevoAut->estados.cant] = nuevoNum;
                    nuevoAut->estados.cant = nuevoAut->estados.cant + 1;
                }
                int numEstadoDesde = nuevoNombreEstado(pAlistaEstadosAIterar->arreglo);
                // Creo la representacion del nuevo estado, y la del estado de listaEstadosResultado
                int nuevoNum = nuevoNombreEstado(conjuntoNuevoArr);
                //agrego transicion
                anadirTransicion(nuevoAut, numEstadoDesde, alfabetoSinLambda.arreglo[i], nuevoNum);
            }
            pAlistaEstadosResultado = listaEstadosResultado->head;
        }
        pAlistaEstadosAIterar = pAlistaEstadosAIterar->next;
    }

    //hasta aca anda

    // si consegui al menos un conjunto nuevo, llamada recursiva
    if(listaEstadosNuevosAIterar.head != NULL){
        cicloNuevosConjuntos(aut, nuevoAut,listaEstadosNuevosAIterar, listaEstadosResultado, alfabetoSinLambda);
    }
    //free(pAlista);
    //free(pAlista2);
}

/*
 * 4 1000
 * 3 100
 * 2 10
 * 1 1
 */
int nuevoNombreEstado(ArregloEnt conjuntoNuevo){
    int nuevoNum = 0;
    int n = conjuntoNuevo.cant;
    int aux;
    if( n == 1){
        return conjuntoNuevo.arreglo[0];
    }else{
        aux = 1;
        for(int j = 0; j < n-1; j++ ){
            aux = aux * 10;
        }
        for(int i = 0; i < conjuntoNuevo.cant; i++){
            nuevoNum = nuevoNum + (conjuntoNuevo.arreglo[i] * aux);
            aux = aux/10;
        }
    }
    return nuevoNum;
}

ListEnt clausuraLambda(Automata aut, ArregloEnt estados){
    // Recorrer todos los estados de ArregloEnt estados
    // por cada estado recorrer la lista en la matriz[estado[i]][z]
    // por lo que me da, lo agrego a la lista resultado
    int indiceLambda = indiceSimbolo(aut, 'z');
    ListEnt result;
    result.head = NULL;

    for(int i = 0; i < estados.cant; i++){
        int indiceEst = indiceEstado(aut, estados.arreglo[i]);
        NodoEnt *aux = aut.delta[indiceEst][indiceLambda].head;
        if(aux != NULL){
            while( aux != NULL){
                /*
                NodoEnt *new_node = (NodoEnt *)malloc(sizeof(NodoEnt));
                new_node->info = aux->info;
                new_node->next = NULL;

                if (result.head == NULL) {
                    result.head  = new_node;
                } else {
                    NodoEnt *aux2 = result.head;
                    result.head = new_node;
                    result.head->next = aux2;
                }
                */
                // chequear si por otro lambda llego a otro estado
                // calculo la clausera lambda del estado anterior que agrego a result
                // si encuentro algo, lo inserto en result
                ArregloEnt aux3;
                aux3.arreglo[0] = aux->info;
                aux3.cant = 1;
                ArregloEnt aux4;
                ListEnt aux5;
                aux5 = clausuraLambda(aut, aux3);
                aux4 = listEntToArray(&aux5);
                for( int j = 0; j < aux4.cant; j++){
                    //insertarEnt(&result, aux4.arreglo[j]);
                    insertarEnt(&result,aux4.arreglo[j]);
                }

                aux = aux->next;
            }
        }
    }
    ArregloEnt resultArray = listEntToArray(&result);
    // me debo asegurar que en resultArray queden los estados del parametro clauseraLambda
    for(int j = 0; j < estados.cant; j++){
        int esta = 0;
        for(int k = 0; k < resultArray.cant; k++){
            if(estados.arreglo[j] == resultArray.arreglo[k]){
                esta = 1;
            }
        }
        if(esta == 0){
            insertarEnt(&result,estados.arreglo[j]);
        }
    }
    return result;
}

ListEnt mover(Automata aut, ArregloEnt estados, char simbolo){
    int indiceSimb = indiceSimbolo(aut, simbolo);
    ListEnt result;
    result.head = NULL;

    for(int i = 0; i < estados.cant; i++){
        int indiceEst = indiceEstado(aut, estados.arreglo[i]);
        NodoEnt *aux = aut.delta[indiceEst][indiceSimb].head;
        if(aux != NULL){
            while( aux != NULL){
                if(esRepetido(result, aux->info) == 0){
                    NodoEnt *new_node = (NodoEnt *)malloc(sizeof(NodoEnt));
                    new_node->info = aux->info;
                    new_node->next = NULL;

                    if (result.head == NULL) {
                        result.head  = new_node;
                    } else {
                        NodoEnt *aux2 = result.head;
                        result.head = new_node;
                        result.head->next = aux2;
                    }
                }
                aux = aux->next;
            }
        }
    }

    //elimino posibles estados repetidos
    //ArregloEnt arregloARetornar = listEntToArray(&result);
    //eliminarRepetidos(&arregloARetornar);
    //freeListEnt(result);
    //return ArrayToListEnt(arregloARetornar);
    return result;
}

int indiceEstado(Automata aut, int estado){
    for(int i = 0; i < aut.estados.cant; i++){
        if(aut.estados.arreglo[i] == estado){
            return i;
        }
    }
    return -1;
}

int indiceSimbolo(Automata aut, char simbolo){
    for(int i = 0; i < aut.simbolos.cant; i++){
        if(aut.simbolos.arreglo[i] == simbolo){
            return i;
        }
    }
    return -1;
}

void freeDelta(Automata aut){
    for(int i = 0; i < aut.estados.cant; i++){
        for(int j = 0; j < aut.simbolos.cant; j++){
            freeListEnt(aut.delta[i][j]);
        }
    }
}

void mostrarAutomata(Automata aut){
    printf("Su alfabeto es: [");
    for(int j = 0; j < aut.simbolos.cant; j++){
        printf("%c ",aut.simbolos.arreglo[j]);
    }
    printf("] \n");

    printf("Sus estados son: [");
    for(int j = 0; j < aut.estados.cant; j++){
        printf("%d ",aut.estados.arreglo[j]);
    }
    printf("] \n");

    printf("Su estado inicial es: %d \n", aut.estadoInicial);

    printf("Sus estados finales son: [");
    for (int j = 0; j < aut.finales.cant; j++){
        printf("%d", aut.finales.arreglo[j]);
    }
    printf("] \n");

    printf("Transiciones: \n");
    for (int i = 0; i < aut.estados.cant; i++) {
        for (int j = 0; j < aut.simbolos.cant; j++) {
            printf("[%d][%c]: ", aut.estados.arreglo[i], aut.simbolos.arreglo[j]);
            NodoEnt *aux = aut.delta[i][j].head;
            if(aux == NULL){
                printf("Lista vacia\n");
            }else{
                while(aux != NULL){
                    printf("%i ",aux->info);
                    aux= aux->next;
                }
                printf("\n");
            }

        }
    }

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "linkedlist.h"
#include "arreglo.h"

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

Automata unionAut(Automata a, Automata b){
    estadosRepetidos(&a, b);
    ArregloEnt nuevosEstados;
    nuevosEstados = unionArregloEnt(a.estados, b.estados);

    ArregloChar nuevoAlfabeto;
    nuevoAlfabeto = unionArregloChar(a.simbolos, b.simbolos);

    int nuevoInicial = 100;

    ArregloEnt nuevosFinales;
    nuevosFinales = unionArregloEnt(a.finales, b.finales);

    Automata nuevoAut = crearAutomata(nuevoAlfabeto, nuevosEstados, nuevoInicial, nuevosFinales);
    nuevoAut.estados.arreglo[nuevoAut.estados.cant] = nuevoInicial;
    nuevoAut.estados.cant++;

    anadirTransicion(&nuevoAut, nuevoInicial, 'z', a.estadoInicial);
    anadirTransicion(&nuevoAut, nuevoInicial, 'z', b.estadoInicial);

    for(int i = 0; i < a.estados.cant; i++){
        for(int j = 0; j < a.simbolos.cant; j++){
            int indiceEst = indiceEstado(a, a.estados.arreglo[i]);
            int indiceSimb = indiceSimbolo(a, a.simbolos.arreglo[j]);
            NodoEnt *aux = a.delta[indiceEst][indiceSimb].head;
            while( aux != NULL){
                anadirTransicion(&nuevoAut, a.estados.arreglo[i], a.simbolos.arreglo[j], aux->info);
                aux = aux->next;
            }
        }
    }
    for(int k = 0; k < b.estados.cant; k++){
        for(int p = 0; p < b.simbolos.cant; p++){
            int indiceEst = indiceEstado(b, b.estados.arreglo[k]);
            int indiceSimb = indiceSimbolo(b, b.simbolos.arreglo[p]);
            NodoEnt *aux = b.delta[indiceEst][indiceSimb].head;
            while( aux != NULL){
                anadirTransicion(&nuevoAut, b.estados.arreglo[k], b.simbolos.arreglo[p], aux->info);
                aux = aux->next;
            }
        }
    }
    return nuevoAut;
}

void estadosRepetidos(Automata *a, Automata b){
    ArregloEnt repetidos;
    repetidos.cant = 0;

    for(int i = 0; i < a->estados.cant; i++){
        int esta = 0;
        for(int j = 0 ; j < b.estados.cant; j++){
            if( a->estados.arreglo[i] == b.estados.arreglo[j]){
                esta = 1;
            }
        }
        if( esta == 1){
            repetidos.arreglo[repetidos.cant] = a->estados.arreglo[i];
            repetidos.cant++;
        }
    }

    for( int k = 0; k < repetidos.cant; k++){
        int estadoActual = repetidos.arreglo[k];
        int indiceEstadoActual = indiceEstado( *a, estadoActual);
        int nuevoNumEstado = estadoActual + 10;
        a->estados.arreglo[a->estados.cant] = nuevoNumEstado;
        a->estados.cant++;
        for( int p = 0; p < a->simbolos.cant; p++){
            int indiceSimb = indiceSimbolo(*a, a->simbolos.arreglo[p]);
            NodoEnt *aux = a->delta[indiceEstadoActual][indiceSimb].head;
            while( aux != NULL){
                anadirTransicion(a, nuevoNumEstado, a->simbolos.arreglo[p], aux->info);
                aux = aux->next;
            }
            int indiceEstadoNuevo = indiceEstado(*a, nuevoNumEstado);
            a->delta[indiceEstadoActual][indiceSimb].head = a->delta[indiceEstadoNuevo][indiceSimb].head;
            a->delta[indiceEstadoNuevo][indiceSimb].head = NULL;
        }
        a->estados.arreglo[indiceEstadoActual] = nuevoNumEstado;
        a->estados.cant--;

        for(int j = 0; j < a->estados.cant; j++){
            for(int h = 0; h < a->simbolos.cant; h++){
                int indiceEst = indiceEstado(*a, a->estados.arreglo[j]);
                int indiceSim = indiceSimbolo(*a, a->simbolos.arreglo[h]);
                NodoEnt *aux2 = a->delta[indiceEst][indiceSim].head;
                while( aux2 != NULL){
                    if( aux2->info == estadoActual){
                        aux2->info = nuevoNumEstado;
                    }
                    aux2 = aux2->next;
                }
            }
        }
    }
}


Automata concatenarAut(Automata a, Automata b){
    estadosRepetidos(&a, b);
    ArregloEnt nuevosEstados;
    nuevosEstados = unionArregloEnt(a.estados, b.estados);

    ArregloChar nuevoAlfabeto;
    nuevoAlfabeto = unionArregloChar(a.simbolos, b.simbolos);

    int nuevoInicial = a.estadoInicial;

    ArregloEnt nuevosFinales;
    nuevosFinales = b.finales;

    Automata nuevoAut = crearAutomata(nuevoAlfabeto, nuevosEstados, nuevoInicial, nuevosFinales);

    for( int h = 0; h < a.finales.cant; h++){
        anadirTransicion(&nuevoAut, a.finales.arreglo[h], 'z', b.estadoInicial);
    }

    for(int i = 0; i < a.estados.cant; i++){
        for(int j = 0; j < a.simbolos.cant; j++){
            int indiceEst = indiceEstado(a, a.estados.arreglo[i]);
            int indiceSimb = indiceSimbolo(a, a.simbolos.arreglo[j]);
            NodoEnt *aux = a.delta[indiceEst][indiceSimb].head;
            while( aux != NULL){
                anadirTransicion(&nuevoAut, a.estados.arreglo[i], a.simbolos.arreglo[j], aux->info);
                aux = aux->next;
            }
        }
    }
    for(int k = 0; k < b.estados.cant; k++){
        for(int p = 0; p < b.simbolos.cant; p++){
            int indiceEst = indiceEstado(b, b.estados.arreglo[k]);
            int indiceSimb = indiceSimbolo(b, b.simbolos.arreglo[p]);
            NodoEnt *aux = b.delta[indiceEst][indiceSimb].head;
            while( aux != NULL){
                anadirTransicion(&nuevoAut, b.estados.arreglo[k], b.simbolos.arreglo[p], aux->info);
                aux = aux->next;
            }
        }
    }
    return nuevoAut;
}

Automata clausuraKlenneAut(Automata a){
    ArregloEnt nuevosEstados;
    nuevosEstados = a.estados;

    ArregloChar nuevoAlfabeto;
    nuevoAlfabeto = a.simbolos;

    int inicialOriginales = a.estadoInicial;

    ArregloEnt finalesOriginales;
    finalesOriginales = a.finales;

    Automata nuevoAut = crearAutomata(nuevoAlfabeto, nuevosEstados, inicialOriginales, finalesOriginales);

    for(int i = 0; i < a.estados.cant; i++){
        for(int j = 0; j < a.simbolos.cant; j++){
            int indiceEst = indiceEstado(a, a.estados.arreglo[i]);
            int indiceSimb = indiceSimbolo(a, a.simbolos.arreglo[j]);
            NodoEnt *aux = a.delta[indiceEst][indiceSimb].head;
            while( aux != NULL){
                anadirTransicion(&nuevoAut, a.estados.arreglo[i], a.simbolos.arreglo[j], aux->info);
                aux = aux->next;
            }
        }
    }

    int nuevoInicial = nuevoAut.estadoInicial + 10;
    nuevoAut.estadoInicial = nuevoInicial;

    ArregloEnt nuevoFinal;
    nuevoFinal.arreglo[0] = nuevoAut.estadoInicial + 10;
    nuevoFinal.cant = 1;
    nuevoAut.finales = nuevoFinal;

    nuevoAut.estados.arreglo[nuevoAut.estados.cant] = nuevoInicial;
    nuevoAut.estados.cant++;
    nuevoAut.estados.arreglo[nuevoAut.estados.cant] = nuevoFinal.arreglo[0];
    nuevoAut.estados.cant++;

    int indiceEstadoInicialOriginal = indiceEstado(a, a.estadoInicial);
    anadirTransicion(&nuevoAut, nuevoAut.estadoInicial, 'z', nuevoAut.estados.arreglo[indiceEstadoInicialOriginal]);
    for(int k = 0; k < a.finales.cant; k++){
        int indiceEstadoFinalOriginal = indiceEstado(a, a.finales.arreglo[k]);
        anadirTransicion(&nuevoAut, nuevoAut.estados.arreglo[indiceEstadoFinalOriginal], 'z', nuevoAut.finales.arreglo[0]);
    }
    anadirTransicion(&nuevoAut, nuevoAut.estadoInicial, 'z', nuevoAut.finales.arreglo[0]);
    anadirTransicion(&nuevoAut, nuevoAut.finales.arreglo[0], 'z', nuevoAut.estadoInicial);

    return  nuevoAut;
}

Automata minimizacionAut(Automata a){
    ArregloEnt estadosNoFinales = diferenciaArregloEnt(a.estados, a.finales);
    ListOfArraysEnt listaParticiones;
    insertarArr(&listaParticiones, estadosNoFinales);
    insertarArr(&listaParticiones, a.finales);
    ArrayOfArraysEnt claseEquivalencia;
    claseEquivalencia.cant = 0;
    // int representanteEstadosNoFinales = estadosNoFinales.arreglo[0];
    // int representanteFinales = a.finales.arreglo[0];
    ListChar alfabetoSinLambdaL;
    for(int g = 0; g < a.simbolos.cant; g++){
        if(a.simbolos.arreglo[g] != 'z'){
            insertarChar(&alfabetoSinLambdaL, a.simbolos.arreglo[g]);
        }
    }
    ArregloChar alfabetoSinLambda = listCharToArray(&alfabetoSinLambdaL);
    for( int i = 0; i < a.estados.cant; i++){
        int indiceEstadoi = indiceEstado(a, a.estados.arreglo[i]);
        for(int j = 0; j < alfabetoSinLambda.arreglo[j]; j++){
            int indiceSimb = indiceSimbolo(a, a.simbolos.arreglo[j]);
            NodoEnt *aux = a.delta[indiceEstadoi][indiceSimb].head;
            if( aux != NULL ){
                NodoArr *pListaParticiones = listaParticiones.head;
                while( pListaParticiones != NULL){
                    int esta = 0;
                    for(int k = 0; k < pListaParticiones->arreglo.cant; k++){
                        if( aux->info == pListaParticiones->arreglo.arreglo[k] ){
                            esta = 1;
                        }
                    }
                    if( esta == 1){
                        claseEquivalencia.array[indiceEstadoi].arreglo[claseEquivalencia.array[indiceEstadoi].cant] = pListaParticiones->arreglo.arreglo[0];
                        claseEquivalencia.array[indiceEstadoi].cant++;
                    }
                    pListaParticiones = pListaParticiones->next;
                }
            }else{
                claseEquivalencia.array[indiceEstadoi].arreglo[claseEquivalencia.array[indiceEstadoi].cant] = -1;
                claseEquivalencia.array[indiceEstadoi].cant++;
            }
        }
    }
    refinarClasesEquivalencia(a, &claseEquivalencia, &listaParticiones);
    // Construir el nuevo automata
    /*ArregloEnt estados;       // Estados son numeros
    ArregloChar simbolos;     // Simbolos del alfabeto son caracteres
    ListEnt delta[MAX][MAX];   // Filas son estados, columnas son simbolos, cada elemento de la matriz es una lista
    ArregloEnt finales;
    int estadoInicial;*/
    
    ArregloChar nuevoAlfabeto;
    nuevoAlfabeto.cant = 0;
    nuevoAlfabeto = a.simbolos;

    ArregloEnt nuevosEstados;
    nuevosEstados.cant = 0;
    
    NodoArr *pListaParticiones = listaParticiones.head;
    while( pListaParticiones != NULL){
        nuevosEstados.arreglo[nuevosEstados.cant] = pListaParticiones->arreglo.arreglo[0];
        nuevosEstados.cant++;
        pListaParticiones = pListaParticiones->next;
    }    

    int nuevoEstadoInicial;
    pListaParticiones = listaParticiones.head;
    while( pListaParticiones != NULL){
        for(int h = 0; h < pListaParticiones->arreglo.cant; h++){
            if(a.estadoInicial == pListaParticiones->arreglo.arreglo[h]){
                nuevoEstadoInicial = pListaParticiones->arreglo.arreglo[h];
            }
        }
        pListaParticiones = pListaParticiones->next;
    }

    ArregloEnt finalesNuevos;
    finalesNuevos.cant = 0;
    pListaParticiones = listaParticiones.head;
    while( pListaParticiones != NULL){
        ArregloEnt interseccionFinalesParticion = interseccionArregloEnt(a.finales,pListaParticiones->arreglo);
        if( interseccionFinalesParticion.cant != 0){
            finalesNuevos.arreglo[finalesNuevos.cant] = pListaParticiones->arreglo.arreglo[0];
            finalesNuevos.cant++;
        }
        pListaParticiones = pListaParticiones->next;
    }

    Automata nuevoAut = crearAutomata(nuevoAlfabeto, nuevosEstados, nuevoEstadoInicial, finalesNuevos);

    pListaParticiones = listaParticiones.head;
    


}

void refinarClasesEquivalencia(Automata a, ArrayOfArraysEnt *claseEquivalencia, ListOfArraysEnt *listaParticiones){
    NodoArr *pListaParticiones = listaParticiones->head;
    ListOfArraysEnt listaParticionesNuevas;
    int refinar = 0;
    while( pListaParticiones != NULL) {
        // Chequear si todas las clases de equivalencia son iguales
        if( clasesEquivalenciaIguales(a, pListaParticiones->arreglo, *claseEquivalencia) == 1){
            // En caso que si, se agrega la particion a la listaParticionesNuevas
            insertarArr( &listaParticionesNuevas,pListaParticiones->arreglo);
            

        }else{
            refinar = 1;
            // Guardar en un arreglo aquellas particiones que tienen las mismas clases de equivalencia
            ArrayOfArraysEnt estadosRepetidos;
            estadosRepetidos.cant = 0;
            for(int i = 0; i < pListaParticiones->arreglo.cant; i++) {
                int indiceEstadoi = indiceEstado(a, pListaParticiones->arreglo.arreglo[i]);
                for(int j = 0; j < pListaParticiones->arreglo.cant; j++){
                    int indiceEstadoj = indiceEstado(a, pListaParticiones->arreglo.arreglo[j]);
                    if(igualdadArreglosEnt(claseEquivalencia->array[indiceEstadoi], claseEquivalencia->array[indiceEstadoj]) == 0){
                        estadosRepetidos.array[estadosRepetidos.cant] =  claseEquivalencia->array[indiceEstadoj];
                        estadosRepetidos.cant++;
                    }
                }
            }
            // Primero identificar aquellas particiones que tienen las mismas clases de equivalencia con la ayuda del arreglo anteriormente obtenido
            // para luego crear una nueva particion con sus clases de equivalencia
            for( int k = 0; k < estadosRepetidos.cant; k++){
                ArregloEnt arregloEstadosIguales;
                arregloEstadosIguales.cant = 0;
                for(int h = 0; h < pListaParticiones->arreglo.cant; h++){
                    int indiceEstadoh = indiceEstado(a, pListaParticiones->arreglo.arreglo[h]);
                    if( igualdadArreglosEnt(estadosRepetidos.array[k], claseEquivalencia->array[indiceEstadoh]) == 1){
                        arregloEstadosIguales.arreglo[arregloEstadosIguales.cant] = pListaParticiones->arreglo.arreglo[h];
                        arregloEstadosIguales.cant++;
                    }
                }
                insertarArr(&listaParticionesNuevas,arregloEstadosIguales);
            }
        }
        pListaParticiones = pListaParticiones->next;
    }
    // Renombramiento
    ListChar alfabetoSinLambdaL;
    for(int k = 0; k < a.simbolos.cant; k++){
        if(a.simbolos.arreglo[k] != 'z'){
            insertarChar(&alfabetoSinLambdaL, a.simbolos.arreglo[k]);
        }
    }
    ArregloChar alfabetoSinLambda = listCharToArray(&alfabetoSinLambdaL);
    for( int i = 0; i < a.estados.cant; i++){
        int indiceEstadoi = indiceEstado(a, a.estados.arreglo[i]);
        for(int j = 0; j < alfabetoSinLambda.arreglo[j]; j++){
            int indiceSimb = indiceSimbolo(a, a.simbolos.arreglo[j]);
            NodoEnt *aux = a.delta[indiceEstadoi][indiceSimb].head;
            if( aux != NULL ){
                NodoArr *pListaParticionesNuevas = listaParticionesNuevas.head;
                while( pListaParticionesNuevas != NULL){
                    int esta = 0;
                    for(int k = 0; k < pListaParticionesNuevas->arreglo.cant; k++){
                        if( aux->info == pListaParticionesNuevas->arreglo.arreglo[k] ){
                            esta = 1;
                        }
                    }
                    if( esta == 1){
                        claseEquivalencia->array[indiceEstadoi].arreglo[claseEquivalencia->array[indiceEstadoi].cant] = pListaParticionesNuevas->arreglo.arreglo[0];
                        claseEquivalencia->array[indiceEstadoi].cant++;
                    }
                    pListaParticionesNuevas = pListaParticionesNuevas->next;
                }
            }else{
                claseEquivalencia->array[indiceEstadoi].arreglo[claseEquivalencia->array[indiceEstadoi].cant] = -1;
                claseEquivalencia->array[indiceEstadoi].cant++;
            }
        }
    }
    // Llamada recursiva
    if( refinar == 1 ){
        refinarClasesEquivalencia(a, claseEquivalencia, &listaParticionesNuevas);
    }
}

int clasesEquivalenciaIguales(Automata a, ArregloEnt particion, ArrayOfArraysEnt clasesEquivalencia){
    int iguales = 1;
    for(int i = 0; i < particion.cant; i++){
        int indiceEstadoi = indiceEstado(a, particion.arreglo[i]);
        for(int j = 0; j < particion.cant; j++){
            int indiceEstadoj = indiceEstado(a, particion.arreglo[j]);
            if( igualdadArreglosEnt(clasesEquivalencia.array[indiceEstadoi], clasesEquivalencia.array[indiceEstadoj]) == 0){
                iguales = 0;
            }
        }
    }
    return iguales;
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
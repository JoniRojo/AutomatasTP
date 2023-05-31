#include <stdio.h>
#include <malloc.h>
#include "automata.h"
#include "archivo.h"
#include <string.h>

/*
int main(){

    FILE* aux;                                      // Archivo donde meteremos todo el automata
    FILE* origin;                                   // Archivo donde tenemos muchos strings
    char cadAux[50];
    char cadena[50];                                // Cadena que toma lo guardado dentro del archivo
    char simbolosRep[20];                           // Guardaremos todos los simbolos del alfabeto.
    char estadosRep[20];                            // Guardaremos todos los estados del automata.
    char final[20];                                 // Guardaremos los estados finales
    int inicial;                                    // Estado inicial del automota
    int cantEstados = 0;                            // Cantidad de estados
    int cantSimbolos = 0;                           // Cantidad de simbolos
    int cantFinales = 0;                            // Cantidad de finales
    int p = 0;                                      // Variable para incrementear los finales
    int w = 0;                                      // Variable para incrementar los estados
    int y = 0;                                      // Variable para incrementar los simbolos
    origin = fopen("origin.txt", "r");            // Abrimos el archivo para lectura
    if (origin != NULL) {                                        // Si la cadena abrio con exito ocurre lo siguiente
        aux = fopen("aut.txt","r+");              //Abrimos el archivo para escribir
        while (!feof(origin)){                             // Mientras no llegemos al final
            fgets(cadena, 50, origin);                  // Leemos un string linea por linea hasta encontrar el automata y reescribirlo en otro .txt
            if(strstr(cadena,"digraph{") != NULL){
                fputs(cadena,aux);

            }else if(strstr(cadena, "inic[shape=point];") != NULL){
                fputs(cadena,aux);

            }else if(strstr(cadena, "inic->") != NULL){
                fputs(cadena,aux);
                char caracter = cadena[6];
                int comoEntero = caracter - '0';
                inicial = comoEntero;

            }else if(strstr(cadena, "->") != NULL){
                fputs(cadena,aux);
                if(existe(estadosRep,cadena[0],cantEstados) == 1){
                    estadosRep[w] = cadena[0];
                    w++;
                    cantEstados++;
                }
                if(existe(estadosRep,cadena[3],cantEstados) == 1){
                    estadosRep[w] = cadena[3];
                    w++;
                    cantEstados++;
                }
                int num = 13;
                int auxiliar = 0;
                auxiliar = cantSim(cadena,cadena[12]);
                for(int r = 0; r < auxiliar; r++){
                    if(existeSim(simbolosRep,cadena[num],cantSimbolos) == 1){
                        simbolosRep[y] = cadena[num];
                        num = num + 2;
                        cantSimbolos++;
                        y++;
                    }
                }

            }else if(strstr(cadena, "doublecircle") != NULL){
                fputs(cadena,aux);
                final[p] = cadena[0];
                p++;
                cantFinales++;

            }else if(cadena[0] == '}'){
                fputs(cadena,aux);
            }
        }
        fclose(aux);
        fclose(origin);
    }

    // Ingresamos todos los estados,simbolos, estado inicial y finales. Para crear el automota
    ListChar listaAlfabeto;
    for(int i = 0; i < cantSimbolos; i++){
        insertarChar(&listaAlfabeto,simbolosRep[i]);
    }
    ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

    ListEnt listaEstados;
    for(int j = 0; j < cantEstados; j++){
        char caracter = estadosRep[j];
        int comoEntero = caracter - '0';
        insertarEnt(&listaEstados, comoEntero);
    }
    ArregloEnt estados = listEntToArray(&listaEstados);

    ListEnt listaFinales;
    for(int t = 0; t < cantFinales; t++){
        char caracter = final[t];
        int comoEntero = caracter - '0';
        insertarEnt(&listaFinales,comoEntero);
    }
    ArregloEnt finales = listEntToArray(&listaFinales);

    Automata a = crearAutomata( alfabeto, estados, inicial, finales);

    // Una vez creado el automata, vamos a añadir todas las transiciones para ver si la cadena es acepta o no
    aux = fopen("aut.txt","r");
    if(aux != NULL){
        while(!feof(aux)){
            fgets(cadAux, 50, origin);
            if(strstr(cadAux, "[label") != NULL){
                char caracter1 = cadAux[0];
                int comoEntero1 = caracter1 - '0';
                printf("%i",comoEntero1);

                char caracter2 = cadAux[3];
                int comoEntero2 = caracter2 - '0';
                printf("%i",comoEntero2);

                int n = 13;
                int b = cantSim(cadAux,cadAux[12]);
                for(int r = 0; r < b; r++){
                    anadirTransicion(&a, comoEntero1, cadAux[n], comoEntero2);
                    n = n + 2;
                }
            }
        }
        fclose(aux);
    }

    mostrarAutomata(a); // Mostramos nuestro automata

    char cad[] = {'a','b', 'b'}; // Ingresamos la cadena para ser evaluada
    int n = 3;
    pertenece(a, cad, n); // Imprimimos si la cadena pertenece o no al automata
}
*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "archivo.c"

int main(){

    FILE* aux;                                    // Archivo donde meteremos todo el automata
    FILE* origin;                                 // Archivo donde tenemos muchos strings
    char cadAux[50];
    char cadena[50];                              // Cadena que toma lo guardado dentro del archivo
    char simbolosRep[20];                         // Guardaremos todos los simbolos del alfabeto.
    char estadosRep[20];                          // Guardaremos todos los estados del automata.
    char final[20];                             // Guardaremos los estados finales
    int inicial;                                 // Estado inicial del automota
    int cantEstados = 0;                          // Cantidad de estados
    int cantSimbolos = 0;                         // Cantidad de simbolos
    int cantFinales = 0;                          // Cantidad de finales
    int p = 0;                                    // Variable para incrementear los finales
    int w = 0;                                    // Variable para incrementar los estados
    int y = 0;                                    // Variable para incrementar los simbolos
    origin = fopen("origin.txt", "r");            // Abrimos el archivo para lectura
    if (origin != NULL) {                         // Si la cadena abrio con exito ocurre lo siguiente
        aux = fopen("aut.txt","r+");              //Abrimos el archivo para escribir
        while (!feof(origin)){                    // Mientras no llegemos al final
          fgets(cadena, 50, origin);              // Leemos un string linea por linea hasta encontrar el digraph
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

  printf("Su estado inicial es: %i \n",inicial);

  printf("Sus estados son: [");
  for(int i = 0; i < cantEstados; i++){
    printf("%c,",estadosRep[i]);
  }
  printf("]\n");
  printf("Sus simbolos son: [");
  for(int j = 0; j < cantSimbolos; j++){
    printf("%c,",simbolosRep[j]);
  }
  printf("]\n");

  printf("Sus finales son: [");
  for(int t = 0; t < cantFinales; t++){
    printf("%c,",final[t]);
  }
  printf("]\n");
  
  aux = fopen("aut.txt","r");
  if(aux != NULL){
    while(!feof(aux)){
       fgets(cadAux, 50, origin);
       if(strstr(cadAux, "[label") != NULL){
          int n = 13;
          int a = cantSim(cadAux,cadAux[12]);
          for(int r = 0; r < a; r++){
          printf("La transicion es %c de %c por el simbolo %c \n",cadAux[0],cadAux[3],cadAux[n]);
          n = n + 2;
          }
        }
    }
    fclose(aux);
  }


    return 1;
}


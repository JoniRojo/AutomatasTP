#include <stdio.h>
#include <string.h>
#include "archivo.h"

int existe(char estadosRep[20],char i,int cant){
    for(int j = 0; j < cant; j++){ // Ciclamos el arreglo de los estados
        if(estadosRep[j] == i){ // Y preguntamos si ese estado ya esta dentro del arreglo de estados
            return -1;
        }
    }
    return 1;
}

int existeSim(char simbolosRep[20],char i,int cant){
    for(int j = 0; j < cant; j++){ // Ciclamos el arreglo de los estados
        if(simbolosRep[j] == i){ // Y preguntamos si ese simbolo ya esta en el arreglo de simbolos
            return -1;
        }
    }
    return 1;
}

int existeFin(char finales[20],char i,int cant){
    for(int j = 0; j < cant; j++){ // Ciclamos el arreglo de los estados
        if(finales[j] == i){ // Y preguntamos si ese estado final no esta repetido en el arreglo de finales
            return -1;
        }
    }
    return 1;
}

int cantSim(char cadena[20],char i){
    int aux = 0;
    int j = 14;
    while(cadena[j] != i){
        aux++;
        j = j + 2;
    }
    aux++;
    return aux;
}

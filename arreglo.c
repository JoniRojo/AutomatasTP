#include "arreglo.h"

void eliminarRepetidos(ArregloEnt *arreglo){
    ArregloEnt arregloAux;
    arreglo->cant = 0;
    if(arreglo->cant != 1){
        arregloAux.arreglo[0] = arreglo->arreglo[0];
        arregloAux.cant = 1;

        for(int i = 1; i < arreglo->cant; i++){
            for (int j = 0; j < arregloAux.cant; ++j) {
                if(arreglo->arreglo[i] != arregloAux.arreglo[j]){
                    arregloAux.arreglo[arregloAux.cant] = arreglo->arreglo[i];
                    arregloAux.cant++;
                }
            }
        }

        for(int k = 0; k < arregloAux.cant; k++){
            arreglo->arreglo[k] = arregloAux.arreglo[k];
        }
        arreglo->cant = arregloAux.cant;
    }
}

ArregloEnt unionArregloEnt(ArregloEnt a, ArregloEnt b){
    ArregloEnt result;
    result.cant = 0;
    for(int i = 0; i < a.cant; i++){
        result.arreglo[i] = a.arreglo[i];
        result.cant++;
    }
    for(int j = 0; j < b.cant; j++){
        int esta = 0;
        for(int k = 0; k < a.cant; k++){
            if(b.arreglo[j] == a.arreglo[k]){
                esta = 1;
            }
        }
        if( esta == 0 ){
            result.arreglo[result.cant] = b.arreglo[j];
            result.cant++;
        }
    }
    return result;
}

ArregloChar unionArregloChar(ArregloChar a, ArregloChar b){
    ArregloChar result;
    result.cant = 0;
    for(int i = 0; i < a.cant; i++){
        result.arreglo[i] = a.arreglo[i];
        result.cant++;
    }
    for(int j = 0; j < b.cant; j++){
        int esta = 0;
        for(int k = 0; k < a.cant; k++){
            if(b.arreglo[j] == a.arreglo[k]){
                esta = 1;
            }
        }
        if( esta == 0 ){
            result.arreglo[result.cant] = b.arreglo[j];
            result.cant++;
        }
    }
    return result;
}


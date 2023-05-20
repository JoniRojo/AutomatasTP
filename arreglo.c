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
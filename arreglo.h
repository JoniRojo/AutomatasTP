#ifndef TP_ARREGLO_H
#define TP_ARREGLO_H
#define MAX2 50

typedef struct ArregloEnt{
    int arreglo[MAX2];
    int cant;
} ArregloEnt;

typedef struct ArregloChar{
    char arreglo[MAX2];
    int cant;
}ArregloChar;

typedef struct ArrayOfArraysEnt{
    ArregloEnt array[MAX2];
    int cant;
}ArrayOfArraysEnt;

void eliminarRepetidos(ArregloEnt *arreglo);

ArregloEnt unionArregloEnt(ArregloEnt a, ArregloEnt b);

ArregloEnt interseccionArregloEnt(ArregloEnt a, ArregloEnt b);

ArregloChar unionArregloChar(ArregloChar a, ArregloChar b);

ArregloEnt diferenciaArregloEnt(ArregloEnt a, ArregloEnt b);

int igualdadArreglosEnt(ArregloEnt a, ArregloEnt b);

#endif //TP_ARREGLO_H

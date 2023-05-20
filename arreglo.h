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

void eliminarRepetidos(ArregloEnt *arreglo);

#endif //TP_ARREGLO_H

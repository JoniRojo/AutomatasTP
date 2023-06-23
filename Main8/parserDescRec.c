#include <stdio.h>
#include <malloc.h>
#define MAX3 20
/*
typedef struct NodoChar{
    char info;
    struct NodoChar *next;
} NodoChar;

typedef struct ListChar{
    NodoChar *head;
} ListChar;

typedef struct ArrayOfListChar{
    ListChar array[MAX3];
    int cant;
} ArrayOfListChar;

void insertarChaR(ListChar *list, char c);

void avanzar(int *indiceCC);

int perteneceSD(ListChar list, char ER[], int indiceCC);

void produccionS(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
void produccionE(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
void produccionEP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
void produccionT(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
void produccionTP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
void produccionF(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
void produccionFP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
void produccionP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
void produccionL(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);

int main(){
    int indiceCC = 0;
    char ER[20] = "a.b|c*#";
    int bool = 1;

    ArrayOfListChar producciones;
    producciones.cant = 0;

    for( int i = 0; i < MAX3; i++){
        producciones.array[i].head = NULL;
    }

    //Las produccion enumeradas en el arreglo de listas:
    //0- S → E #
    //1- E → T E'
    //2- E' → | T E'
    //3- E' → Lambda
    //4- T → F T'
    //5- T' → . F T'
    //6- T' → Lambda
    //7- F → P F'
    //8- F' → *
    //9- F' → Lambda
    //10- P → ( E )
    //11- P → L
    //12- L → a
    //13- L → b
    //14- L → c


    insertarChaR(&producciones.array[0], '(');
    insertarChaR(&producciones.array[0], 'a');
    insertarChaR(&producciones.array[0], 'b');
    insertarChaR(&producciones.array[0], 'c');
    producciones.cant++;

    insertarChaR(&producciones.array[1], '(');
    insertarChaR(&producciones.array[1], 'a');
    insertarChaR(&producciones.array[1], 'b');
    insertarChaR(&producciones.array[1], 'c');
    insertarChaR(&producciones.array[1], ')');
    producciones.cant++;

    insertarChaR(&producciones.array[2], '|');
    producciones.cant++;

    insertarChaR(&producciones.array[3], '#');
    insertarChaR(&producciones.array[3], ')');
    producciones.cant++;

    insertarChaR(&producciones.array[4], '(');
    insertarChaR(&producciones.array[4], 'a');
    insertarChaR(&producciones.array[4], 'b');
    insertarChaR(&producciones.array[4], 'c');
    producciones.cant++;

    insertarChaR(&producciones.array[5], '.');
    producciones.cant++;

    insertarChaR(&producciones.array[6], '|');
    insertarChaR(&producciones.array[6], ')');
    insertarChaR(&producciones.array[6], '#');
    producciones.cant++;

    insertarChaR(&producciones.array[7], '(');
    insertarChaR(&producciones.array[7], 'a');
    insertarChaR(&producciones.array[7], 'b');
    insertarChaR(&producciones.array[7], 'c');
    producciones.cant++;

    insertarChaR(&producciones.array[8], '*');
    producciones.cant++;

    insertarChaR(&producciones.array[9], '.');
    insertarChaR(&producciones.array[9], '|');
    insertarChaR(&producciones.array[9], ')');
    insertarChaR(&producciones.array[9], '#');
    producciones.cant++;

    insertarChaR(&producciones.array[10], '(');
    producciones.cant++;

    insertarChaR(&producciones.array[11], 'a');
    insertarChaR(&producciones.array[11], 'b');
    insertarChaR(&producciones.array[11], 'c');
    producciones.cant++;

    insertarChaR(&producciones.array[12], 'a');
    producciones.cant++;

    insertarChaR(&producciones.array[13], 'b');
    producciones.cant++;

    insertarChaR(&producciones.array[14], 'c');
    producciones.cant++;

    produccionS(producciones, &bool, ER, &indiceCC);

    if(bool == 1){
        printf("La expresion regular %s es reconocida \n", ER);
    } else {
        printf("La expresion regular %s no es reconocida \n", ER);
    }
}

void insertarChaR(ListChar *list, char c){
    NodoChar *new_node = (NodoChar *)malloc(sizeof(NodoChar));
    new_node->info = c;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        NodoChar *aux = list->head;
        list->head  = new_node;
        list->head->next = aux;
    }
}

void avanzar(int *indiceCC){
    *indiceCC = *indiceCC + 1;
}

int perteneceSD(ListChar list, char ER[], int indiceCC){
    NodoChar *aux = list.head;
    while(aux != NULL){
        if(aux->info == ER[indiceCC]){
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

void produccionS(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(perteneceSD(producciones.array[0], ER, *indiceCC) == 1){
        produccionE(producciones, bool, ER, indiceCC);
        if(ER[*indiceCC] == '#'){
            *bool = 1;
        } else{
            *bool = 0;
        }
    } else {
        *bool = 0;
    }
}

void produccionE(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[1], ER, *indiceCC) == 1){
            produccionT(producciones, bool, ER, indiceCC);
            produccionEP(producciones, bool, ER, indiceCC);
        } else {
            *bool = 0;
        }
    }
}

void produccionEP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[2], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == '|'){
                avanzar(indiceCC);
            } else{
                *bool = 0;
            }
            produccionT(producciones, bool, ER, indiceCC);
            produccionEP(producciones, bool, ER, indiceCC);
        } else if(perteneceSD(producciones.array[3], ER, *indiceCC) == 1){
           //skip
        } else {
            *bool = 0;
        }
    }
}

void produccionT(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if( *bool == 1){
        if(perteneceSD(producciones.array[4], ER, *indiceCC) == 1){
            produccionF(producciones, bool, ER, indiceCC);
            produccionTP(producciones, bool, ER, indiceCC);
        } else {
            *bool = 0;
        }
    }
}

void produccionTP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if (*bool == 1){
        if(perteneceSD(producciones.array[5], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == '.'){
                avanzar(indiceCC);
            } else{
                *bool = 0;
            }
            produccionF(producciones, bool, ER, indiceCC);
            produccionTP(producciones, bool, ER, indiceCC);
        } else if(perteneceSD(producciones.array[6], ER, *indiceCC) == 1){
            //skip
        } else{
            *bool = 0;
        }
    }
}

void produccionF(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if( *bool == 1){
        if(perteneceSD(producciones.array[7], ER, *indiceCC) == 1){
            produccionP(producciones, bool, ER, indiceCC);
            produccionFP(producciones, bool, ER, indiceCC);
        } else {
            *bool = 0;
        }
    }
}

void produccionFP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[8], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == '*'){
                avanzar(indiceCC);
            } else {
                *bool = 0;
            }
        } else if(perteneceSD(producciones.array[9], ER, *indiceCC) == 1){
            //skip
        } else{
            *bool = 0;
        }
    }
}

void produccionP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[10], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == '('){
                avanzar(indiceCC);
            } else {
                *bool = 0;
            }
            produccionE(producciones, bool, ER, indiceCC);
            if(ER[*indiceCC] == ')'){
                avanzar(indiceCC);
            } else {
                *bool = 0;
            }
        } else if(perteneceSD(producciones.array[11], ER, *indiceCC) == 1){
            produccionL(producciones, bool, ER, indiceCC);
        } else {
            *bool = 0;
        }
    }
}

void produccionL(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[12], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == 'a'){
                avanzar(indiceCC);
            } else {
                *bool = 0;
            }
        } else if(perteneceSD(producciones.array[13], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == 'b') {
                avanzar(indiceCC);
            } else{
                *bool = 0;
            }
        } else if(perteneceSD(producciones.array[14], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == 'c'){
                avanzar(indiceCC);
            } else {
                *bool = 0;
            }
        } else{
            *bool = 0;
        }
    }
}
*/
#include <stdio.h>
#include <malloc.h>
#define MAX3 20

#include "../automata.h"
/*
// Esta estrutura va en arreglo.h pero, por motivos desconocidos, no funciona bien el
// #include "linkedlist.h" necesario de la linea 11, tipo de error que tambien deberia
// saltar cuando en linkedlist.h se hace un #include "arreglo.h", pero no es así...
typedef struct ArrayOfListChar{
    ListChar array[MAX3];
    int cant;
} ArrayOfListChar;

void insertarChaR(ListChar *list, char c);

void avanzar(int *indiceCC);

int perteneceSD(ListChar list, char cadena[], int indiceCC);

Automata produccionS(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
Automata produccionE(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
Automata produccionEP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
Automata produccionT(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
Automata produccionTP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
Automata produccionF(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
Automata produccionFP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
Automata produccionP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);
Automata produccionL(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC);

int main(){
    int indiceCC = 0;
    char ER[20] = "a|b#";
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

    Automata result = produccionS(producciones, &bool, ER, &indiceCC);
    if(bool == 1){
        printf("La expresion regular %s es reconocida \n", ER);
    } else {
        printf("La expresion regular %s no es reconocida \n", ER);
    }
    printf("AFND generado: \n");
    mostrarAutomata(result);
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

Automata produccionS(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(perteneceSD(producciones.array[0], ER, *indiceCC) == 1){
        Automata autFinal = produccionE(producciones, bool, ER, indiceCC);
        if(ER[*indiceCC] == '#'){
            *bool = 1;
        } else{
            *bool = 0;
            Automata error;
            return error;
        }
        return autFinal;
    } else {
        *bool = 0;
        Automata error;
        return error;
    }
}

Automata produccionE(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[1], ER, *indiceCC) == 1){
            Automata prodT = produccionT(producciones, bool, ER, indiceCC);
            int aux = *indiceCC;
            Automata prodEP = produccionEP(producciones, bool, ER, indiceCC);
            if(aux != *indiceCC){
                return unionAut(prodT,prodEP);
            } else {
                return prodT;
            }
        } else {
            *bool = 0;
            Automata error;
            return error;
        }
    }
    Automata error;
    return error;
}

Automata produccionEP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[2], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == '|'){
                avanzar(indiceCC);
            } else{
                *bool = 0;
                Automata error;
                return error;
            }
            Automata prodT = produccionT(producciones, bool, ER, indiceCC);
            int aux = *indiceCC;
            Automata prodEP = produccionEP(producciones, bool, ER, indiceCC);
            if(aux != *indiceCC){
                return unionAut(prodT,prodEP);
            } else {
                return prodT;
            }
        } else if(perteneceSD(producciones.array[3], ER, *indiceCC) == 1){
            //skip
        } else {
            *bool = 0;
            Automata error;
            return error;
        }
    }
    Automata error;
    return error;
}

Automata produccionT(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if( *bool == 1){
        if(perteneceSD(producciones.array[4], ER, *indiceCC) == 1){
            Automata prodF = produccionF(producciones, bool, ER, indiceCC);
            int aux = *indiceCC;
            Automata prodTP = produccionTP(producciones, bool, ER, indiceCC);
            if(aux != *indiceCC) {
                return concatenarAut(prodF,prodTP);
            } else {
                return prodF;
            }
        } else {
            *bool = 0;
            Automata error;
            return error;
        }
    }
    Automata error;
    return error;
}

Automata produccionTP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if (*bool == 1){
        if(perteneceSD(producciones.array[5], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == '.'){
                avanzar(indiceCC);
            } else{
                *bool = 0;
                Automata error;
                return error;
            }
            Automata prodF = produccionF(producciones, bool, ER, indiceCC);
            int aux = *indiceCC;
            Automata prodTP = produccionTP(producciones, bool, ER, indiceCC);
            if(aux != *indiceCC){
                return concatenarAut(prodF, prodTP);
            } else {
                return prodF;
            }
        } else if(perteneceSD(producciones.array[6], ER, *indiceCC) == 1){
            //skip
        } else{
            *bool = 0;
            Automata error;
            return error;
        }
    }
    Automata error;
    return error;
}

Automata produccionF(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if( *bool == 1){
        if(perteneceSD(producciones.array[7], ER, *indiceCC) == 1){
            Automata prodP = produccionP(producciones, bool, ER, indiceCC);
            int aux = *indiceCC;
            produccionFP(producciones, bool, ER, indiceCC);
            if(aux != *indiceCC) {
                return clausuraKlenneAut(prodP);
            } else {
                return prodP;
            }
        } else {
            *bool = 0;
            Automata error;
            return error;
        }
    }
    Automata error;
    return error;
}

Automata produccionFP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[8], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == '*'){
                avanzar(indiceCC);
            } else {
                *bool = 0;
                Automata error;
                return error;
            }
        } else if(perteneceSD(producciones.array[9], ER, *indiceCC) == 1){
            //skip
        } else{
            *bool = 0;
            Automata error;
            return error;
        }
    }
    Automata error;
    return error;
}

Automata produccionP(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[10], ER, *indiceCC) == 1){
            Automata parentesisAbre;
            Automata parentesisCierra;
            Automata concat;
            if(ER[*indiceCC] == '('){
                avanzar(indiceCC);

                ListChar listaAlfabeto1;
                insertarChar(&listaAlfabeto1, '(');
                insertarChar(&listaAlfabeto1, 'z');
                ArregloChar alfabeto1 = listCharToArray(&listaAlfabeto1);

                ListEnt listaEstados1;
                listaEstados1.head = NULL;
                insertarEnt(&listaEstados1, 7);
                insertarEnt(&listaEstados1, 8);
                ArregloEnt estados1 = listEntToArray(&listaEstados1);

                int inicial1 = 7;
                ListEnt listaFinales1;
                listaFinales1.head = NULL;
                insertarEnt(&listaFinales1,8);
                ArregloEnt finales1 = listEntToArray(&listaFinales1);

                parentesisAbre = crearAutomata( alfabeto1, estados1, inicial1, finales1);
                anadirTransicion(&parentesisAbre,7,'(',8);
            } else {
                *bool = 0;
                Automata error;
                return error;
            }
            concat = concatenarAut(parentesisAbre,  produccionE(producciones, bool, ER, indiceCC));
            if(ER[*indiceCC] == ')'){
                avanzar(indiceCC);

                ListChar listaAlfabeto2;
                insertarChar(&listaAlfabeto2, ')');
                insertarChar(&listaAlfabeto2, 'z');
                ArregloChar alfabeto2 = listCharToArray(&listaAlfabeto2);

                ListEnt listaEstados2;
                listaEstados2.head = NULL;
                insertarEnt(&listaEstados2, 9);
                insertarEnt(&listaEstados2, 10);
                ArregloEnt estados2 = listEntToArray(&listaEstados2);

                int inicial2 = 9;
                ListEnt listaFinales2;
                listaFinales2.head= NULL;
                insertarEnt(&listaFinales2,10);
                ArregloEnt finales2 = listEntToArray(&listaFinales2);

                parentesisCierra = crearAutomata( alfabeto2, estados2, inicial2, finales2);
                anadirTransicion(&parentesisCierra,9,')',10);

                Automata result = concatenarAut(concat, parentesisCierra);
                return result;
            } else {
                *bool = 0;
                Automata error;
                return error;
            }
        } else if(perteneceSD(producciones.array[11], ER, *indiceCC) == 1){
            return produccionL(producciones, bool, ER, indiceCC);
        } else {
            *bool = 0;
            Automata error;
            return error;
        }
    }
    Automata error;
    return error;
}

Automata produccionL(ArrayOfListChar producciones, int *bool, char ER[], int *indiceCC){
    if(*bool == 1){
        if(perteneceSD(producciones.array[12], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == 'a'){
                avanzar(indiceCC);
                ListChar listaAlfabeto;
                listaAlfabeto.head = NULL;
                insertarChar(&listaAlfabeto, 'a');
                insertarChar(&listaAlfabeto, 'z');
                ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

                ListEnt listaEstados;
                listaEstados.head = NULL;
                insertarEnt(&listaEstados, 1);
                insertarEnt(&listaEstados, 2);
                ArregloEnt estados = listEntToArray(&listaEstados);

                int inicial = 1;
                ListEnt listaFinales;
                listaFinales.head = NULL;
                insertarEnt(&listaFinales,2);
                ArregloEnt finales = listEntToArray(&listaFinales);

                Automata a = crearAutomata( alfabeto, estados, inicial, finales);
                anadirTransicion(&a,1,'a',2);

                return a;
            } else {
                *bool = 0;
                Automata error;
                return error;
            }
        } else if(perteneceSD(producciones.array[13], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == 'b') {
                avanzar(indiceCC);
                ListChar listaAlfabeto;
                listaAlfabeto.head = NULL;
                insertarChar(&listaAlfabeto, 'b');
                insertarChar(&listaAlfabeto, 'z');
                ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

                ListEnt listaEstados;
                listaEstados.head = NULL;
                insertarEnt(&listaEstados, 3);
                insertarEnt(&listaEstados, 4);
                ArregloEnt estados = listEntToArray(&listaEstados);

                int inicial = 3;
                ListEnt listaFinales;
                listaFinales.head = NULL;
                insertarEnt(&listaFinales,4);
                ArregloEnt finales = listEntToArray(&listaFinales);

                Automata b = crearAutomata( alfabeto, estados, inicial, finales);
                anadirTransicion(&b,3,'b',4);

                return b;
            } else{
                *bool = 0;
                Automata error;
                return error;
            }
        } else if(perteneceSD(producciones.array[14], ER, *indiceCC) == 1){
            if(ER[*indiceCC] == 'c'){
                avanzar(indiceCC);
                ListChar listaAlfabeto;
                listaAlfabeto.head = NULL;
                insertarChar(&listaAlfabeto, 'c');
                insertarChar(&listaAlfabeto, 'z');
                ArregloChar alfabeto = listCharToArray(&listaAlfabeto);

                ListEnt listaEstados;
                listaEstados.head = NULL;
                insertarEnt(&listaEstados, 5);
                insertarEnt(&listaEstados, 6);
                ArregloEnt estados = listEntToArray(&listaEstados);

                int inicial = 5;
                ListEnt listaFinales;
                listaFinales.head = NULL;
                insertarEnt(&listaFinales,6);
                ArregloEnt finales = listEntToArray(&listaFinales);

                Automata c = crearAutomata( alfabeto, estados, inicial, finales);
                anadirTransicion(&c,5,'c',6);

                return c;
            } else {
                *bool = 0;
                Automata error;
                return error;
            }
        } else{
            *bool = 0;
            Automata error;
            return error;
        }
    }
    Automata error;
    return error;
}
*/
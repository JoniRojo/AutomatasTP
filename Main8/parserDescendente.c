  #include <stdio.h>
#include <malloc.h>

typedef struct NodoChar{
    char info;
    struct NodoChar *next;
} NodoChar;

typedef struct NodoEnt{
    int info;
    struct NodoEnt *next;
    struct NodoChar *simbolos;
    struct NodoChar *producion;
    
} NodoEnt;

typedef struct ListEnt{
   NodoEnt *head;
} ListEnt;

void insertarEnt(ListEnt *list, int info);

void insertarChar(ListEnt *list,NodoEnt **auxiliar,int cant, char cadena[cant]);

void avanzar();

void mostrarListSimbolos(ListEnt *list);

void mostrarListProduction(ListEnt *list);

void searchProduction(ListEnt *list, int num, int cant, char cadena[]);

void createProduction(ListEnt *list, int num, int cant, char cadena[]);

void insertarProduction(ListEnt *list,NodoEnt **auxiliar, int cant, char cadena[100]);

int perteneceSD(ListEnt *list,int elementoCorriente,int num, char cadena[]);

void produccionS();

void produccionE();

void produccionEP();

void produccionT();

void produccionTP();

void produccionF();

void produccionFP();

void produccionP();

void produccionL();

char cadena[100] = "a*|b#";
int elementoCorriente = 0;
ListEnt list;

int main(){

  list.head = NULL;
  // Generamos todas las producciones de manera creciente, pero nosotros por defecto sabemos a que produccion pertenece
  for(int i = 15; i > 0; i--){
    insertarEnt(&list,i);
  }

  list.head->producion = NULL;

  // É = A
  // T' = O
  // F' = I
  
  createProduction(&list,1,2,"E#");
  createProduction(&list,2,2,"TA");
  createProduction(&list,3,3,"|TA");
  createProduction(&list,4,1,"z");
  createProduction(&list,5,2,"FO");
  createProduction(&list,6,3,".FO");
  createProduction(&list,7,1,"z");
  createProduction(&list,8,2,"PI");
  createProduction(&list,9,1,"*");
  createProduction(&list,10,1,"z");
  createProduction(&list,11,3,"(E)");
  createProduction(&list,12,1,"L");
  createProduction(&list,13,1,"a");
  createProduction(&list,14,1,"b");
  createProduction(&list,15,1,"c");
  
  list.head->simbolos = NULL;

  searchProduction(&list,1,4,"(abc");
  searchProduction(&list,2,4,"(abc)");
  searchProduction(&list,3,1,"|");
  searchProduction(&list,4,2,"#)");
  searchProduction(&list,5,4,"(abc");
  searchProduction(&list,6,1,".");
  searchProduction(&list,7,3,"|)#");
  searchProduction(&list,8,4,"(abc");
  searchProduction(&list,9,1,"*");
  searchProduction(&list,10,4,".|)#");
  searchProduction(&list,11,1,"(");
  searchProduction(&list,12,3,"abc");
  searchProduction(&list,13,1,"a");
  searchProduction(&list,14,1,"b");
  searchProduction(&list,15,1,"c");

  produccionS();
  

  return 0;
}

void insertarEnt(ListEnt *list, int info){
    NodoEnt *new_node = (NodoEnt *)malloc(sizeof(NodoEnt));
    new_node->info = info;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        NodoEnt *aux = list->head;
        list->head  = new_node;
        list->head->next = aux;
    }
}

// Se agrega los simbolos directrices a su produccion correspondiente
void insertarChar(ListEnt *list,NodoEnt **auxiliar, int cant, char cadena[100]){

    for(int i = 0; i < cant; i++){
    NodoChar *aux = malloc(sizeof(NodoChar));
    aux->info = cadena[i];
    aux->next = (*auxiliar)->simbolos;
    (*auxiliar)->simbolos = aux;
  }
  
}

// Buscamos la produccion e invocamos a la funcion de insetarChar para agregar sus simbolos directrices
void searchProduction(ListEnt *list, int num, int cant, char cadena[]){
  NodoEnt *auxiliar = list->head;
  while(auxiliar != NULL){
    if(auxiliar->info == num){
      insertarChar(list,&auxiliar,cant,cadena);
      break;
    }
    auxiliar = auxiliar->next;
  }

}

// Esta funcion es para buscar la produccion y crear la parte derecha de esa misma produccion.
void createProduction(ListEnt *list, int num, int cant, char cadena[]){
  NodoEnt *auxiliar = list->head;
  while(auxiliar != NULL){
    if(auxiliar->info == num){
      insertarProduction(list,&auxiliar,cant,cadena);
      break;
    }
    auxiliar = auxiliar->next;
  }

}

void insertarProduction(ListEnt *list,NodoEnt **auxiliar, int cant, char cadena[100]){

    for(int i = 0; i < cant; i++){
    NodoChar *aux = malloc(sizeof(NodoChar));
    aux->info = cadena[i];
    aux->next = (*auxiliar)->producion;
    (*auxiliar)->producion = aux;
  }
  
}


// Funcion para mostrar la lista de producciones con sus simbolos directrices
void mostrarListSimbolos(ListEnt *list){
  NodoEnt *aux = list->head;
  while(aux !=NULL){
    printf("Numero: %i",aux->info);
    NodoChar *aux1 = aux->simbolos;
    printf("\n");
    printf("La lista de simbolos directices: ");
    while(aux1 != NULL){
      printf("%c",aux1->info);
      aux1 = aux1->next;
      
    }
    printf("\n");
    aux = aux->next;
  }
}

void mostrarListProduction(ListEnt *list){
  NodoEnt *aux = list->head;
  while(aux !=NULL){
    printf("Numero: %i",aux->info);
    NodoChar *aux1 = aux->producion;
    printf("\n");
    printf("Parte derecha: ");
    while(aux1 != NULL){
      printf("%c",aux1->info);
      aux1 = aux1->next;
      
    }
    printf("\n");
    aux = aux->next;
  }
}

// Accion para que el elemento corriente avanze en la cadena
void avanzar(){
  elementoCorriente = elementoCorriente + 1;
}

int perteneceSD(ListEnt *list,int elementoCorriente,int num,char cadena[]){
  NodoEnt *aux = list->head;
  while(aux != NULL){
    if(aux->info == num){
    NodoChar *var = aux->simbolos;

    while(var != NULL){
      if(var->info == cadena[elementoCorriente]){
        return 1;
        break;
      }
      var = var->next;
    }
    }
    aux = aux->next;
  }
  return 0;
}

// Todas las funciones para cada No Terminal de la gramatica
void produccionS(){
  if(perteneceSD(&list,elementoCorriente,1,cadena) == 1){
    
    produccionE();

    if(cadena[elementoCorriente] == '#'){
      printf("Aceptar");
    }
  } else {
    printf("Error");
  }
}

void produccionE(){
  if(perteneceSD(&list,elementoCorriente,2,cadena) == 1){
  
      produccionT();

      produccionEP();
    
  } else {
    printf("Error");
  }
}

void produccionEP(){
  if(perteneceSD(&list,elementoCorriente,3,cadena) == 1){
    if(cadena[elementoCorriente] == '|'){
      avanzar();
    }
    produccionT();
  
    produccionEP();
    
  } else if(perteneceSD(&list,elementoCorriente,4,cadena) == 1){
    if(cadena[elementoCorriente] == 'z'){
      avanzar();
    } else {
      printf("Error");
    }
  } else {
    printf("Error");
  }
}

void produccionT(){
  if(perteneceSD(&list,elementoCorriente,5,cadena) == 1){
    
    produccionF();
  
    produccionTP();
    
  } else {
    printf("Error");
  }
}

void produccionTP(){
  if(perteneceSD(&list,elementoCorriente,6,cadena) == 1){
    if(cadena[elementoCorriente] == '.'){
      avanzar();
    } 
      
    produccionF();
    
    produccionTP();
    
  } else if(perteneceSD(&list,elementoCorriente,7,cadena) == 1){
    if(cadena[elementoCorriente] == 'z'){
      avanzar();
    } else{
      printf("Error");
    }
  } else{
    printf("Error");
  }
}

void produccionF(){
  if(perteneceSD(&list,elementoCorriente,8,cadena) == 1){
    
    produccionP();
  
    produccionFP();
    
  } else {
    printf("Error");
  }
}

void produccionFP(){
  if(perteneceSD(&list,elementoCorriente,9,cadena) == 1){
    if(cadena[elementoCorriente] == '*'){
      avanzar();
    } else {
      printf("Error");
    }
  } else if(perteneceSD(&list,elementoCorriente,10,cadena) == 1){
    if(cadena[elementoCorriente] == 'z'){
      avanzar();
    } else {
      printf("Error");
    }
  } else{
    printf("Error");
  }
}

void produccionP(){
  if(perteneceSD(&list,elementoCorriente,11,cadena) == 1){
    if(cadena[elementoCorriente] == '('){
      avanzar();
    } 
    
    produccionE();
    
    if(cadena[elementoCorriente] == ')'){
      avanzar();
    } else {
      printf("Error");
    }
  } else if(perteneceSD(&list,elementoCorriente,12,cadena) == 1){
      produccionL();
  } else {
    printf("Error");
  }
}

void produccionL(){
  if(perteneceSD(&list,elementoCorriente,13,cadena) == 1){
    if(cadena[elementoCorriente] == 'a'){
      avanzar();
    } else {
      printf("Error");
    }
  } else if(perteneceSD(&list,elementoCorriente,14,cadena) == 1){
    if(cadena[elementoCorriente] == 'b') {
      avanzar();
    } else{
      printf("Error");
    }
  } else if(perteneceSD(&list,elementoCorriente,15,cadena) == 1){
    if(cadena[elementoCorriente] == 'c'){
      avanzar();
    } else {
      printf("Error");
    }
  } else{
    printf("Error");
  }
}
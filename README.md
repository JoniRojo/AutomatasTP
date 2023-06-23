# AutomatasTP
Integrantes: Rojo Jonathan, Romero Juan Ignacio

Estructura utilizada:
- Estados: enteros, se almacenará en un arreglo de enteros.
- Alfabeto: carácteres, se almacenará en un arreglo de caracteres.
- Se tendrá una variable entera para guardar el estado inicial, y un arreglo de enteros para almacenar aquellos estados finales.
- Transiciones: se utilizará una matriz de lista de enteros, donde la fila son estados, y las columnas, simbolos del alfabeto.

Convenciones:
- El simbolo lambda es una 'z'.
- Todo automata debe tener dentro de su alfabeto el simbolo lamda.
- Los estados son numeros enteros positivos sin incluir el cero.

Para ejecutar un main:
- Comentar el codigo entero de los demás main's( con /* */).
- En la linea 7 del archivo CMakeList.txt, cambiar la ubicación del main al que se quiere ejecutar, por ejemplo:
  add_executable( ... Main7/runMinimizacion.c)

Main's (Aclaraciones importantes en Main 3 y 10):

  - Main1 - PERTENECE: Se crea el automata y se muestra en consola. Luego es invocada la funcion de pertenece con dos cadenas, una que la acepta y la otra que no. Recordar que la funcion pertenece funcionará para AFD y eventualmente sobre un AFND...


  - Main2 - AF TEXTO: Tenemos dos archivos .txt, en donde el archivo "origin.txt" podemos exceder de la  escritura en el documento, que luego sobre el algoritmo lo que va a realizar es eliminar todo aquello que no pertenezca a la estructura y pasarlo al siguiente documento "aut.txt", donde en este se creara el automata correspondiente respecto a la estructura.
  Puede modificar el archivo "origin.txt" y luego correr el main, y ver los cambios en el "aut.txt".


  - Main3 - AFNDtoAFD: Se utiliza el AFND del ejemplo del libro, se ejecuta la funcion AFNDtoAFD y se imprime por consolta el nuevo automata.


  - Main4 - UNION: Utilizamos el ejemplo de libro y creamos ambos automatas, se los muestra por consola para diferenciarlos y luego, utilizamos la funcion de union de automatas y mostramos en consola dicha union.


  - Main5 - CONCATENACION: Utilizamos el ejemplo de libro y creamos ambos automatas, se los muestra por consola para diferenciarlos y luego, utilizamos la funcion de concatenacion de automatas y mostramos en consola dicha concatenacion.


  - Main6 - CLAUSURAKLENNE: Utilizamos el ejemplo de libro y creamos el automata, se lo muestra por consola y luego utilizamos la clausura de Klenne que se muestra por ultimo en consola.


  - Main7 - MINIMIZACION: Utilizamos el ejemplo del Libro y creamos el automata, este se muestra por consola para posteriormente mostar también el automata minimizado.


  - Main8 - TP3EJERCICIO2: Dado la gramatica del TP, corregida para que sea LL(1) (las producciones finales estan comentadas en el main y, los simbolos directrices de cada produccion son insertados en un arreglo de listas). Se realizo el parser descendente recursivo para reconocer expresiones regulares(dadas) segun la gramatica LL(1) definida. Es invocada la funcion con dicha ER y por consola se muestra si la expresion regular es reconocida o no por la gramatica.

  - Main9 - TP3EJERCICIO3: Sobre el parser descendete recursivo que habiamos hecho en el main anterior, este fue sobreescrito para crear un AFND donde, se va construyendo el automata desde las hojas para finalmente ser mostrada por consola.

  - Main10 - TP3EJERCICIO4: Realizamos una funcion minigrep, que concatena un automata, que consume a's b's c's y los ( ) que pueda/quiera , con el automata obtenido por el main anterior, para luego concatenar finalmente con otro automata del estilo del primero. De esta forma dada por ejemplo, la ER a|b y la cadena cccbcc, este automata la reconoce. Sin embargo, dado que la funcion pertenece funciona correctamente para AFD y, aleatoriamente bien para un AFND, en la mayoria de los casos se imprimira por consola que la cadena no es aceptada por el automata, pero si observamos el automata "a papel", nos daremos cuenta que si es aceptada.



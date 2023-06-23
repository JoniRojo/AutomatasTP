# AutomatasTP
Integrantes: Rojo Jonathan, Romero Juan Ignacio

Convenciones:
- Los simbolos son carácteres.
- El simbolo lambda es una 'z'.
- Los estados son numeros enteros positivos sin incluir el cero.

Para ejecutar un main:
- Comentar el codigo entero de los demás main's.
- En la linea 7 del archivo CMakeList.txt, cambiar la ubicación del main al que se quiere ejecutar, por ejemplo:
  add_executable( ... Main7/runMinimizacion.c)

Explicacion sobre los mains:
  -Main1: Se crea el automata y se muestra en consola. Luego es invocada la funcion de pertenece con dos cadenas, una que la acepta y la otra que no.

  -Main2: Tenemos dos archivos .txt, en donde el archivo "origin.txt" podemos exceder de la   escritura en el documento, que luego sobre el algoritmo lo que va a realizar es eliminar todo aquello que no pertenezca a la estructura y pasarlo al siguiente documento "aut.txt", donde en este se creara el automata correspondiente respecto a la estructura.
  Puede modificar el archivo "origin.txt" y luego correr el main, y ver los cambios en el "aut.txt".

  -Main3:

  -Main4: Utilizamos el Ejemplo de libro y creamos los dos automatas, en donde se los muestra por consola para diferenciarlos y despues utilizamos la funcion de union de automatas, para mas tarde mostrarlo en consola a dicha union.

  -Main5: Utilizamos el Ejemplo de libro y creamos los dos automatas, en donde se los muestra por consola para diferenciarlos y despues utilizamos la concatenacion de automatas, para mas tarde mostrarlo en consola a dicha concatenacion.

  -Main6: Utilizamos el Ejemplo de libro y creamos el automata, en donde se lo muestra por consola para diferenciarlo luego de que utilizamos la clausura de Klenne que se muestra por ultimo en consola.

  -Main7: Utilizamos el Ejemolo del Libro y creamos el automata, en se muestra por consola para diferenciarlo con el automata minimizado.

  -Main8: Dado la Gramatica del TP, corregida para que sea LL(1), en donde los simbolos directrices de cada produccion estan comentadas dentro de este main. Se realizo el parser descendente recursivo para reconocer las cadenas denotadas por las expresiones regulares que genere la gramatica. Es invocada la funcion con dicha cadena y por consola se muestra si la expresion regular es reconocida o no.

  -Main9: Sobre el parser descendete recursivo que habiamos hecho en el main anterior, este fue sobreescrito para crear un AFND, en donde se invoca a la funcion y se muestra por pantalla el automata obtenido.

  -Main10: Realizamos una funcion minigrep, que toma el automata obtenido por el main anterior y se muestra por consola. La idea es hacer el automata a papel y tomar varias cadenas como ejemplos y ver si son aceptadas por el automata. Ya que la funcion pertenece solo es para AFD y no para AFND. 



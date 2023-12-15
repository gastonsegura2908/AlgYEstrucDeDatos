# TP1---AyE
### 1. Problema
Desarrollar una máquina que ejecute un programa almacenado en un archivo como una secuencia
de instrucciones. Las instrucciones del programa están escritas en un lenguaje de programación
elemental AYED22, que será descripto a continuación. En el lenguaje AYED22 cada instrucción
ocupa un reglon en el archivo del código fuente. Hay 5 tipos de instrucciones:
##### 1) Declaración de variables.
Las variables serán de tipo entero o booleano, cuyo nombre será de un solo caracter de la ’a’ a la
’z’. Ejemplo:
INT a
BOOL b
INT e
##### 2) Asignación.
Permite asignar un valor entero o booleano a alguna de las variables previamente declaradas. Las
instrucciones de este tipo son de la forma:
Var = expresion aritmetica
o
Var = expresión booleana
donde Var es el nombre de una variable previamente definida expresión aritmética es una expresión
que puede ser un número, una variable o una operacion aritmética cuyos operadores son de las 4
operaciones aritméticas, y como operandos son números enteros o nombres de variables antes
declaradas. Similar para las expresiones booleanas que seran comparaciones con los operadores
==, !=, >, >=, <,<= entre variables y valores . Puede anidar operaciones con paréntesis.
Ejemplo:
a = 4
b = a < 5
e = (a - 2) * 14
##### 3) Condicional.
Es una instrucción IF seguida por condición booleana entre paréntesis THEN instrucción.
Ejemplo: IF (a < 4 ) THEN a = a - 1
la condición booleana tiene como operadores relacionales al igual (==), distinto (!=), menor (<) y
mayor (> ). No hay ELSE.
##### 4) Show.
Es un comando que permite imprimir por pantalla el valor de una expresion aritmetica definida
anteriormente.
Ejemplo:
SHOW a
SHOW b+1
##### 5) Salto.
Cada instrucción del programa tiene asignado un número que representa su posición en la secuencia
del programa, comenzando desde 1. La instrucción JUMP contiene un número que hace referencia
al salto en el flujo de ejecución del programa hacia la instrucción dada por el número. Ejemplo:
JUMP 4
hace un salto a la cuarta instrucción.
### 2. Ejemplo de programa
1. INT a
2. INT b
3. a = 4
4. b = 1
5. BOOL c
6. c = a < 1
7. IF ( c ) THEN JUMP 12
8. b = b * a
9. a = a – 1
10. c = a < 1
11. JUMP 7
12. SHOW b
este programa calcula el factorial de 4
### 3. Restricciones de la Solución
Genere una clase instrucción que sea genérica y que tenga un método “ejecutar()” y que desde esta
se generen subclases acorde a cada tipo de instrucción y que implemente el “ejecutar()” según
corresponda.
La ejecución de cada instrucción es la siguiente:
La declaración de una variable genera un nodo en una lista de variables que contendrá su nombre,
tipo y un valor.
La asignación guarda en la variable de la asignación el valor calculado de la expresión a la derecha
del signo =.
El condicional evalua la instrucción asociada si la expresión booleana vale True.
El Show imprime por pantalla el valor indicado.
El Salto Jump rompe con la secuencia de instrucciones y salta a ejecutar la instrucción indicada.
La máquina ejecuta el programa por medio de la ejecución de cada instrucción en forma secuencial,
una a una, salvo el JUMP que hace un salto a la instrucción indicada.
Debe armar una lista donde se almacenen todas las instrucciones y el ejecutor del programa lea una
a una y las ejecute acorde a su implementacion de “ejecutar()”.
Si no es un JUMP, la máquina luego de ejecutar, avanza a la siguiente en la lista.
Si es un JUMP, debe reposicionarse haciendo el salto a la instrucción indicada y continuar desde ese
punto. Para evaluar la expresión aritmética o booleana use una expresión posfija que evalúa usando
una pila.
Para evaluar la expresión booleana modifique el programa de expresiones aritméticas por uno
donde los operadores sean los relacionales. Deberá utilizar el código de las clases lista y pila dados
en clases prácticas.

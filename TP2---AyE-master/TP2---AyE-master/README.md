# TP2---AyE
## CONSIGNA: Procesamiento de un archivo de formato JSON

Los archivos con formato JSON (JavaScript Object Notation - Notación de Objetos de
JavaScript) tienen un formato ligero y son utilizados para de intercambio de datos. Su definición puede consultar se https://www.json.org/json-es.html y en
https://www.mclibre.org/consultar/informatica/lecciones/formato-json.html
Ud deberá realizar el procesamiento de un archivo, preferentemente el archivo de
descarga desde https://api.nobelprize.org/v1/laureate.json que corresponde a quienes han sido laureados con los premios Nobel.

La estructura de un archivo tiene distintos niveles de profundidad con multiples objetos en cada nivel, por lo que este formato puede verse como un arbol m-ario. En concreto, la información con formato de “arreglo” puede verse como una serie de m-nodos hijos del objeto donde dicho arreglo está contenido.
La lectura del archivo debe cargarse en memoria sobre una estructura de un arbol m-ario.

Este tipo de arbol debe implementarse sobre un arbol binario. La forma de implementar un arbol m-ario sobre un arbol binario es la siguiente:
La raiz del arbol m-ario es la misma que del binario. El hijo más hacia la izq del arbol mario es el izq del binario. Los restantes hijos del m-ario (hermanos del izquierdo), se implementan como una cadena de hijos derechos del primer hijo.

Deberá implementar de esta forma un arbol m-ario sobre un arbol binario. Sobre esta
implementación la inserción de hijos (hermanos) deberá ser de forma tal que permita
reordenarlos una vez cargada toda la información y alternativamente cargarlos en forma ordenada, es decir, cada nuevo nodo que sea hermano de otro (insertado sobre la cadena de la rama derecha), debe quedar insertado en forma ordenada creciente respecto de algun valor que tenga dicho objeto (nombre, pais, fecha nacimiento, etc). Debera implementar un recorrido pre-orden en el m-ario para poder listar el resultado de la carga y ordenamiento, de forma tal que si el ordenamiento fue realizado por fecha de nacimiento, ese sea el orden en que figuren los datos. Una estructura de pila puede ser de ayuda para esta funcionalidad.
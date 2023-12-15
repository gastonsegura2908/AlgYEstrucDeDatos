#pragma once
#ifndef ARBOLM_H
#define ARBOLM_H
#include "../Lista/lista.hpp"
#include "../Nodo/nodoA.hpp"

string eliminar_espacios(string s);
bool mayor(nodo<string> *n1, nodo<string> *n2, string llave, bool es_numero);
bool menor(nodo<string> *n1, nodo<string> *n2, string llave, bool es_numero);
void bubbleSort(Lista<nodo<string> *> *, string, bool);
void quickSort(Lista<nodo<string> *> *lista, int primero, int ultimo, string llave, bool es_numero);
class ArbolM
{
private:
    nodo<string> *raiz;
    void recorrer(nodo<string> *aux, int prof = 0);
    void mh(nodo<string> *aux);
    void crearJson(Lista<string> *json, nodo<string> *&nuevo);
    void ordenar(nodo<string> *aux, string llave, bool es_numero){}; // ordena el arbol de acuerdo a cierta funcion de comparacion

public:
    ArbolM()
    {
        raiz = NULL;
    };
    ~ArbolM() { delete raiz; };
    void CrearJson(Lista<string> *json)
    {
        crearJson(json, raiz);
    }                                           // llena el arbol m-ario a partir de un json guardado en una lista de strings
    void Recorrer() { recorrer(raiz); }         // recorre todos los elementos y los imprime
    nodo<string> *getRaiz() { return raiz; }    // devuelve la raiz
    void MostrarHojas() { mh(raiz); }           // muestra las hojas
    void Ordenar(string llave, bool es_numero); // ordena el arbol de acuerdo a cierta funcion de comparacion
};

void ArbolM::crearJson(Lista<string> *json, nodo<string> *&nuevo)
{
    if (json->esvacia())
    {
        nuevo = NULL;
        return;
    }

    string linea1 = json->pop(); // sacamos una linea.///pop nos devuelve la cabeza de la lista,y la borra de la lista

    string lineaAux = eliminar_espacios(linea1); /// lo que hacemos es eliminar los espacios del string linea1

    if (lineaAux == "{}" || lineaAux == "[]")
        return;

    if (lineaAux == "}" || lineaAux == "]" || lineaAux == "}," || lineaAux == "],")
    {
        // fin de objeto u array
        nuevo = NULL;
        return;
    }

    if (nuevo == NULL) // crear nodo
        nuevo = new nodo<string>;

    if (lineaAux == "{")
    {
        // empieza un objeto

        while (true)
        {
            // iteramos por todos los elementos del objeto agregandolo como hijos
            nodo<string> *nuevoHijo = new nodo<string>;

            // nos metemos en la recursividad del nuevo hijo
            crearJson(json, nuevoHijo);

            if (nuevoHijo == NULL)
            {
                // termino el objeto
                delete nuevoHijo;
                break;
            }

            // agregamos el nodo a la lista de hijos
            nuevo->hijos->add(nuevoHijo);
        }
        nuevo->hijos->invertir(); // para que el primer agregado sea el primero en la lista
        return;
    }

    if (lineaAux == "[")
    {
        // empieza un array
        int pos = 0;
        while (true)
        {
            // iteramos por todos los elementos del array agregandolo como hijos
            nodo<string> *nuevoHijo = new nodo<string>;

            nuevoHijo->info = to_string(pos++);

            // nos metemos en la recursividad del nuevo hijo
            crearJson(json, nuevoHijo);

            if (nuevoHijo == NULL)
            {
                // termino el array
                delete nuevoHijo;
                break;
            }
            // agregamos el nodo a la lista de hijos
            nuevo->hijos->add(nuevoHijo);
        }
        nuevo->hijos->invertir(); // para que el primer agregado sea el primero en la lista
        return;
    }

    if (linea1.find(':') != string::npos)
    {
        // hay una llave
        int end = linea1.find(":");
        string llave = linea1.substr(linea1.find("\"") + 1, end - linea1.find("\"") - 2);
        nuevo->info = llave;

        // nos fijamos cual es el ultimo caracter
        char ultimo = *(linea1.end() - 1);

        if (ultimo == '{')
        {
            // caso su valor es un objeto
            // lo pasamos recursivamente para que la condicion anterior le agregue los hijos
            json->add("{");
            crearJson(json, nuevo);
            return;
        }

        if (ultimo == '[')
        {
            // caso su valor es un array
            // lo pasamos recursivamente para que la condicion anterior le agregue los hijos
            json->add("[");
            crearJson(json, nuevo);
            return;
        }

        if (ultimo == ']' || ultimo == '}')
        {
            // caso objeto u array vacio
            return;
        }
        // caso que asigna un valor

        // extraemos el valor de la linea
        int start = end + 3;
        end = linea1.size() - end - 4;

        if (linea1.find(',') != string::npos)
            end--;

        string valor = linea1.substr(start, end);

        // creamos el nodo hijo
        nodo<string> *nuevoHijo = new nodo<string>;
        nuevoHijo->info = valor;

        nuevo->hijos->add(nuevoHijo);
        return;
    }

    cout << "No se pudo identificar la linea" << endl;
    exit(1);
}

/**
 * @brief Recorre todo el arbol m-ario e imprime los datos de cada nodo
 *
 * @tparam T
 * @param aux - nodo auxiliar
 */
void ArbolM::recorrer(nodo<string> *aux, int prof)
{
    if (aux == NULL)
        return;

    for (int i = 0; i < prof; i++)
        cout << "- ";

    cout << aux->info << endl;

    Lista<nodo<string> *> *hijos_copy = aux->hijos->copy();

    while (true)
    {
        nodo<string> *next = hijos_copy->pop();
        if (next == NULL)
            break;
        recorrer(next, prof + 1);
    }
    delete hijos_copy;
}

void ArbolM::Ordenar(string llave, bool es_numero)
{
    // ordenamos la lista de hijos de laureates
    bubbleSort(raiz->hijos->get(0)->hijos, llave, es_numero);
    // int n = raiz->hijos->get(0)->hijos->size();
    // quickSort(raiz->hijos->get(0)->hijos, 0, n - 1, llave, es_numero);
}

/**
 * @brief Mostrar Hojas
 *
 * @tparam T
 * @param aux - nodo auxiliar
 */
void ArbolM::mh(nodo<string> *aux)
{
    if (aux == NULL)
        return;

    int len = aux->hijos->size();

    if (len == 0)
    {
        // sin hijos, es una hoja
        cout << "\n"
             << aux->info;
    }

    for (int i = 0; i < len; i++)
        mh(aux->hijos->get(i));
}

/**
 * @brief Elimina los espacios de un string
 *
 * @param    s - string a eliminar los espacios
 * @return devuelve un nuevo string sin los espacios
 */
string eliminar_espacios(string s)
{
    string res = "";
    int len = s.size();
    for (int i = 0; i < len; i++)
    {
        char c = s.at(i); // el at devuelve el elemento de la posicion dada como parametro
        if (c == ' ')
            continue;
        res += c;
    }
    return res;
}

/**
 * @brief Compara dos Nodos segun un criterio creciente (de menor a mayor)
 *
 * @param    n1 - Nodo 1
 * @param    n2 - Nodo 2
 * @param    llave - LLave que representa el hijo del nodo
 * @param    es_numero - Bool, true realiza una comparacion booleana n1 < n2
 * @return true si n1 es menor que n2
 * @return false c.c.
 */
bool menor(nodo<string> *n1, nodo<string> *n2, string llave, bool es_numero)
{
    // cout << "nodos:" << n1->info << " < " << n2->info << " valores: ";
    Lista<nodo<string> *> *hijos1_copy = n1->hijos->copy();
    Lista<nodo<string> *> *hijos2_copy = n2->hijos->copy();

    string val1 = "";
    string val2 = "";

    nodo<string> *aux = NULL;

    // buscamos los valores asociados a la llave

    while (!hijos1_copy->esvacia())
    {
        aux = hijos1_copy->pop();
        if (aux->info == llave)
        {
            val1 = aux->hijos->cabeza()->info;
            break;
        }
    }
    if (val1 == "")
    {
        // no se encontro la llave
        return false;
    }

    while (!hijos2_copy->esvacia())
    {
        aux = hijos2_copy->pop();
        if (aux->info == llave)
        {
            val2 = aux->hijos->cabeza()->info;
            break;
        }
    }
    if (val2 == "")
    {
        // no se encontro la llave
        return true;
    }
    // cout << val1 << " < " << val2 << endl;
    delete hijos1_copy, hijos2_copy, aux;

    // comparamos los valores

    try
    {
        if (es_numero)
            return stoi(val1) < stoi(val2);
    }
    catch (const std::exception &e)
    {
        cout << "Error comparando, no se puede convertir a entero";
        std::cerr << e.what() << '\n';
    }

    // si es un string, se ordena alfabeticamente por la primera letra
    return tolower(val1[0]) <= tolower(val2[0]);
};

/**
 * @brief Compara dos Nodos segun un criterio decreciente (de mayor a menor)
 *
 * @param    n1 - Nodo 1
 * @param    n2 - Nodo 2
 * @param    llave - LLave que representa el hijo del nodo
 * @param    es_numero - Bool, true realiza una comparacion booleana n1 >= n2
 * @return true si n1 es mayor o igual que n2
 * @return false c.c.
 */
bool mayor(nodo<string> *n1, nodo<string> *n2, string llave, bool es_numero)
{
    // cout << "nodos:" << n1->info << " > " << n2->info << " valores: ";
    Lista<nodo<string> *> *hijos1_copy = n1->hijos->copy();
    Lista<nodo<string> *> *hijos2_copy = n2->hijos->copy();

    string val1 = "";
    string val2 = "";

    nodo<string> *aux = NULL;

    // buscamos los valores asociados a la llave

    while (!hijos1_copy->esvacia())
    {
        aux = hijos1_copy->pop();
        if (aux->info == llave)
        {
            val1 = aux->hijos->cabeza()->info;
            break;
        }
    }
    if (val1 == "")
    {
        // no se encontro la llave
        cout << "Error sin llave 1" << endl;
        exit(1);
    }

    while (!hijos2_copy->esvacia())
    {
        aux = hijos2_copy->pop();
        if (aux->info == llave)
        {
            val2 = aux->hijos->cabeza()->info;
            break;
        }
    }
    if (val2 == "")
    {
        // no se encontro la llave
        cout << "Error sin llave 2" << endl;
        exit(1);
    }
    // cout << val1 << " > " << val2 << endl;
    delete hijos1_copy, hijos2_copy, aux;

    // comparamos los valores

    try
    {
        if (es_numero)
            return stoi(val1) > stoi(val2);
    }
    catch (const std::exception &e)
    {
        cout << "Error comparando, no se puede convertir a entero";
        std::cerr << e.what() << '\n';
    }

    // si es un string, se ordena alfabeticamente por la primera letra
    return tolower(val1[0]) >= tolower(val2[0]);
};

/**
 * @brief Ordena la lista de nodos con el algoritmo burbuja
 *
 * @param    lista - Lista de nodos
 * @param    llave - Llave a utlizar en la comparacion
 * @param    es_numero - Si la comparacion es de enteros
 */
void bubbleSort(Lista<nodo<string> *> *lista, string llave, bool es_numero)
{
    int n = lista->size();
    bool continuar = true;
    int i = 0;

    while (continuar)
    {
        continuar = false;
        nodo<string> *aux = NULL;
        nodo<string> *aux1 = NULL;

        Nodo<nodo<string> *> nodo_lista = lista->getNodo(0); // Devuelve un Nodo de lista

        for (int j = 0; j < n - i - 1; j++)
        {
            aux = nodo_lista.get_dato();              // nodo j
            aux1 = nodo_lista.get_next()->get_dato(); // nodo j+1

            if (menor(aux1, aux, llave, es_numero))
            {
                swap(*aux1, *aux);
                continuar = true;
            }

            nodo_lista = *nodo_lista.get_next();
        }
        i++;
    }
}

/**
 * @brief Ordena la lista de nodos con el algoritmo quick sort
 *
 * @param    lista - Lista de nodos
 * @param    primero - entero, en la primera iteracion = 0
 * @param    ultimo - entero, en la primera iteracion = size - 1
 * @param    llave - Llave a utlizar en la comparacion
 * @param    es_numero - Si la comparacion es de enteros
 */
void quickSort(Lista<nodo<string> *> *lista, int primero, int ultimo, string llave, bool es_numero)
{
    int i, j;
    nodo<string> *pivot = NULL;
    if (ultimo > primero)
    {
        pivot = lista->get(ultimo);
        i = primero - 1;
        j = ultimo;
        nodo<string> *aux = NULL;

        while (true)
        {
            // ++i < pivot
            Nodo<nodo<string> *> nodo_lista = lista->getNodo(++i);
            while (menor(nodo_lista.get_dato(), pivot, llave, es_numero))
            {
                i++;
                if (nodo_lista.get_next())
                    nodo_lista = *nodo_lista.get_next();
            } // hasta i tengo elementos menores al pivot
            aux = nodo_lista.get_dato();

            // --j > pivot
            Nodo<nodo<string> *> nodo_lista2 = lista->getNodo(--j);
            while (mayor(nodo_lista2.get_dato(), pivot, llave, es_numero))
            {
                if (j == 0)
                    break;
                j--;
                if (nodo_lista2.get_prev())
                    nodo_lista2 = *nodo_lista2.get_prev();
            } // desde j tengo elementos mayores al pivot

            if (i >= j)
                break;

            // swap
            swap(*aux, *nodo_lista2.get_dato());
        }

        // swap elemento_i y ultimo
        swap(*aux, *pivot);
        quickSort(lista, primero, i - 1, llave, es_numero);
        quickSort(lista, i + 1, ultimo, llave, es_numero);
    }
}

#endif
#pragma once
#ifndef GRAFO_H
#define GRAFO_H
#include "../Cola/cola.hpp"
#include "../Arbol/arbolM.hpp"

bool *copiar_array(bool *array, int N);

using namespace std;

/**
 * @brief La clase representa un grafo
 *
 */
class Grafo
{

private:
    // arreglo de adyacencias
    // [ [adyacenciasMA], [adyacenciasRO], [adyacenciasPA], [adyacenciasAM], ... ]
    int V; // Cantidad de vertices
public:
    int **pesos;  // matriz de pesos
    bool **ady;   // matriz de adyacencia, indica si hay relacion entre 2 vertices
    Grafo(int V); // Constructor

    ~Grafo();

    // agregar aristas
    void addArista(int v, int w, int peso);
    void addAristaNoDirigido(int v, int w, int peso);

    // imprime el grafo realizando un recorrido en amplitud
    string BFS(int s);

    // busca caminos hamiltonianos
    ArbolM<int> buscarCiclosHam(int s);
    // revisa las aristas disponibles de cada vertice
    bool revisar_aristas_no_visitados(bool visitados[], int s, int p);
};

/**
 * @brief Construct a new Grafo:: Grafo object
 *
 * @param    V                   Cantidad de Vertices
 */
Grafo::Grafo(int V)
{
    this->V = V;

    // crear una matriz bidimensional de V filas x V columnas
    this->pesos = new int *[V];
    this->ady = new bool *[V];

    for (int i = 0; i < V; i++)
    {
        pesos[i] = new int[V]; // cada fila es un arreglo de enteros y el valor de la celda es el peso
        ady[i] = new bool[V];

        for (int j = 0; j < V; j++)
            ady[i][j] = false; // no hay relacion entre i,j
    }
}

/**
 * @brief Destroy the Grafo:: Grafo object
 */
Grafo::~Grafo()
{
    for (int i = 0; i < V; i++)
    {
        delete pesos[i], ady[i];
        pesos[i] = NULL;
        ady[i] = NULL;
    }
    delete pesos, ady;
    pesos = NULL;
    ady = NULL;
}

/**
 * @brief addArista: agrega una arista entre 2 vertices
 *
 * @param    v                   vertice origen
 * @param    w                   vertice destino
 * @param    peso                peso de la arista
 */
void Grafo::addArista(int v, int w, int peso)
{
    // agrega una relacion entre dos vertices
    ady[v][w] = true;
    pesos[v][w] = peso;
}

/**
 * @brief addArista: agrega una arista entre 2 vertices sin dirigir
 *
 * @param    v                   vertice 1
 * @param    w                   vertice 2
 * @param    peso                peso de la arista
 */
void Grafo::addAristaNoDirigido(int v, int w, int peso)
{
    addArista(v, w, peso);
    addArista(w, v, peso);
}

/**
 * @brief Realiza un recorrido en amplitud del grafo
 *
 * @param    s                   Vertice de Origen
 */
string Grafo::BFS(int s)
{
    // marcar todos los vertices como no visitados
    bool visitados[V];

    for (int i = 0; i < V; i++)
        visitados[i] = false;

    // Crear una cola
    Cola<int> cola = Cola<int>();

    // Marcar el vertice actual como visitado y encolarlo
    visitados[s] = true;
    cola.encolar(s);

    string res = "";

    while (!cola.esvacia())
    {
        // Desencolar vertice de la cola e imprimirlo
        s = cola.pop();

        res += to_string(s) + " ";
        // Buscar todos los vertices adyacentes a s
        // Si el adyacente no fue visitado,
        // entonces marcarlo como visitado y encolarlo

        for (int i = 0; i < V; i++)
        {
            if (ady[s][i] && !visitados[i])
            {
                // vertice i es adyacente a s y no fue visitado
                visitados[i] = true;
                cola.encolar(i);
            }
        }
    }
    return res;
}

/**
 * @brief Busca los caminos hamiltonianos existentes en el grafo partiendo de s
 *
 * @param    s                   Vertice de origen
 * @return arbolM - donde cada rama es un camino hamiltoniano valido
 */
ArbolM<int> Grafo::buscarCiclosHam(int s)
{
    // marcar todos los vertices como no visitados
    bool *visitados;
    visitados = new bool[V];

    for (int i = 0; i < V; i++)
        visitados[i] = false;

    // Crear Cola Auxiliar para los visitados de cada camino
    Cola<bool *> colaVisitados = Cola<bool *>();

    // Crear arbol m-ario
    ArbolM<int> caminos = ArbolM<int>();
    nodo<int> *nodoArbol = new nodo<int>;
    nodoArbol->info = s;
    nodoArbol->der = new nodo<int>(0); // peso acumulado hasta el primer nodo
    nodoArbol->padre = NULL;
    caminos.setRaiz(nodoArbol);

    // Crear una cola
    Cola<nodo<int> *> cola = Cola<nodo<int> *>();

    // encolamos el nodo (ciudad) actual y encolamos lista de visitados
    cola.encolar(nodoArbol);
    colaVisitados.encolar(visitados);

    while (!cola.esvacia())
    {
        // Desencolar vertice de la cola
        nodoArbol = cola.pop();

        // Desencolar lista de visitados hasta el vertice s
        visitados = colaVisitados.pop();

        // verificamos la cantidad de aristas disponibles
        bool es_valido = revisar_aristas_no_visitados(visitados, s, nodoArbol->info);

        // si no es valido, cualquier combinacion de caminos subsiguiente tampoco es valida
        if (!es_valido)
        {
            // borramos el nodo de la lista de hijos del padre
            // y verificamos que el padre tenga otros hijos,
            // si no tiene otros hijos entonces el padre tambien es invalido y lo borramos
            do
            {

                if (nodoArbol->padre == NULL)
                    // se trata de la raiz del arbol
                    break;

                nodo<int> *padre = nodoArbol->padre;

                padre->hijos->borrarDato(nodoArbol); // eliminamos el puntero de la lista del padre

                nodoArbol = padre;

            } while (nodoArbol->hijos->esvacia());

            continue;
        }

        // marcar nodo actual como visitado
        visitados[nodoArbol->info] = true;

        // agregar todos los adyacentes (y no visitados) de nodoArbol como hijos
        for (int i = 0; i < V; i++)
        {
            if (ady[nodoArbol->info][i] && !visitados[i])
            {
                nodo<int> *nuevoHijo = new nodo<int>;
                nuevoHijo->info = i;
                nuevoHijo->padre = nodoArbol;
                nuevoHijo->der = new nodo<int>(nodoArbol->der->info + pesos[nodoArbol->info][i]);
                nodoArbol->hijos->add(nuevoHijo);

                // encolamos (una copia)
                colaVisitados.encolar(copiar_array(visitados, V));
                cola.encolar(nuevoHijo);
            }
        }

        // verificamos si se visitaron todos los vertices
        bool todos_visitados = true;
        for (int j = 0; j < V; j++)
        {
            if (!visitados[j])
            {
                todos_visitados = false;
                break;
            }
        }

        if (todos_visitados)
            // si se visitaron todos los vertices y hay adyacencia
            // entre el ultimo nodo y el nodo de origen entonces
            // es un ciclo hamiltoniano y lo conectamos al origen
            if (ady[nodoArbol->info][s])
            {
                nodo<int> *nuevoHijo = new nodo<int>;
                nuevoHijo->info = s;
                nuevoHijo->der = new nodo<int>(nodoArbol->der->info + pesos[nodoArbol->info][s]);
                nodoArbol->hijos->add(nuevoHijo);
            }

        delete visitados; // liberamos los punteros
        visitados = NULL;
    }
    return caminos;
}

/**
 * @brief Revisa las aristas de los vertices no visitados
 * para validar si es posible crear un ciclo hamiltoniano
 *
 * @param  visitados             - array de vertices visitados
 * @param  s                     - vertice de origen
 * @return true                  - es valido el ciclo
 * @return false                 - no es valido el ciclo (aristas < 2)
 */
bool Grafo::revisar_aristas_no_visitados(bool visitados[], int s, int p)
{
    for (int i = 0; i < V; i++)
    {
        // verifico las aristas disponibles de los no visitados
        if (visitados[i] || i == p)
            continue;

        // solo voy a analizar los no visitados

        int cantidad_de_aristas_de_i = 0;

        for (int j = 0; j < V; j++)
            // si i es adyacente a j y no visite j => sumar arista disponible
            if ((ady[i][j] && !visitados[j]) || (ady[i][s] && j == s))
                cantidad_de_aristas_de_i++;

        if (cantidad_de_aristas_de_i < 2)
            return false;
    }
    return true;
}

/**
 * @brief Copia un array de tamaño N
 *
 * @param    array               Array booleano
 * @param    N                   tamaño del array
 * @return array booleano
 */
bool *copiar_array(bool *array, int N)
{
    bool *array_copia;
    array_copia = new bool[N];

    for (int i = 0; i < N; i++)
        array_copia[i] = array[i];
    return array_copia;
}

#endif
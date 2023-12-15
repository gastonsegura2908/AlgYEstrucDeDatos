#include <iostream>
#include "./clases/Grafo/Grafo.hpp"

string index_to_cities(string recorrido);

using namespace std;

// C O N S T A N T E S
int INFI = 999999;

// Maxima cantidad de vertices (ciudades)
int const VERTICES = 8;

/**
 * @brief printPath: imprime un array de recorrido
 *
 * @param    path Cola
 */
void printPath(Grafo const &graph, int path[], int n)
{
    string s = "";              // inicializa string
    for (int i = 0; i < n; i++) // recorre el path
    {
        if (i < n - 1 && !graph.ady[path[i]][path[i + 1]])
            cout << "ERROR" << endl;
        s += to_string(path[i]) + " "; // "0 1 3 4"
    }
    s += to_string(path[0]);
    cout << index_to_cities(s) << endl; // "MA RO AM ZU"
}
// inicializar visited

/**
 * @brief hamiltonianPaths: busca todos los caminos
 *
 * @param    graph               Grafo
 * @param    v                   Vertice actual
 * @param    visited             array vertices visitados
 * @param    path                camino actual
 * @param    n                   cantidad total de vertices
 */
void hamiltonianPaths(Grafo const &graph, int v, bool visited[], Cola<int> *path, int n)
{
    // si se visitan todos los vértices, entonces existe el camino hamiltoniano
    if (path->size() == n)
    {
        if (graph.ady[path->last()][path->cabeza()])
            // imprime el ciclo hamiltoniano
            printPath(graph, path->colaToArray(), n);
        return;
    }

    // Comprobar si cada arista a partir del vértice `v` conduce a una solución o no
    for (int w = 0; w < n; w++)
    {
        if (!graph.ady[v][w]) // si no son adyacentes continuamos al siguiente
            continue;

        if (visited[w]) // si ya lo visitamos continuamos al siguiente
            continue;

        visited[w] = true;

        path->encolar(w);

        // verifica si agregar el vértice `w` a la ruta conduce a la solución o no
        // ver backtracking: https://www.techiedelight.com/backtracking-interview-questions/
        hamiltonianPaths(graph, w, visited, path, n);

        // retractarse
        visited[w] = false;
        path->borrar();
    }
}

/**
 * @brief findHamiltonianPaths: encuentra todos los ciclos hamiltonianos de un grafo
 *
 * @param    graph               Grafo
 * @param    n                   Cantidad total de vertices
 * @param    start               Vertice en donde empezar el ciclo
 */
void findHamiltonianPaths(Grafo const &graph, int n, int start)
{
    // comienza con cada nodo
    // agrega el vertice inicial a la ruta
    Cola<int> *path = new Cola<int>;
    path->encolar(start);

    // marca el nodo de inicio como visitado
    bool visited[n];

    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    visited[start] = true;

    hamiltonianPaths(graph, start, visited, path, n);
}

string index_to_cities(string recorrido)
{
    string recorrido2 = "";
    for (auto c : recorrido)
    {
        switch (c)
        {
        case '0':
            recorrido2 += "MA ";
            break;
        case '1':
            recorrido2 += "RO ";
            break;
        case '2':
            recorrido2 += "PA ";
            break;
        case '3':
            recorrido2 += "AM ";
            break;
        case '4':
            recorrido2 += "ZU ";
            break;
        case '5':
            recorrido2 += "BE ";
            break;
        case '6':
            recorrido2 += "VA ";
            break;
        case '7':
            recorrido2 += "VI ";
            break;
        default:
            break;
        }
    }
    return recorrido2;
}

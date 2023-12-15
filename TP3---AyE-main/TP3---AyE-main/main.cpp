#include <iostream>
#include "./clases/Grafo/Grafo.hpp"

using namespace std;

// C O N S T A N T E S
int INFI = 999999;

int const VERTICES = 8; // Maxima cantidad de vertices (ciudades)

// P R O T O T I P O S
void convertirGrafo(int M[VERTICES][VERTICES], Grafo *grafo);

// Enumerado de las Ciudades a recorrer
enum ciudades
{
    MA, // 0
    RO, // 1
    PA, // 2
    AM, // 3
    ZU, // 4
    BE, // 5
    VA, // 6
    VI  // 7
};

int main()
{
    int peso[VERTICES][VERTICES] = {
        // MA   RO    PA    AM    ZU     BE   VA    VI
        INFI, INFI, 210, INFI, 300, INFI, 350, 320, // MA
        INFI, INFI, 350, INFI, 150, INFI, 280, 250, // RO
        210, 350, INFI, 100, INFI, 120, INFI, INFI, // PA
        INFI, INFI, 100, INFI, 200, 60, INFI, INFI, // AM
        300, 150, INFI, 200, INFI, 120, INFI, 240,  // ZU
        INFI, INFI, 120, 60, 120, INFI, 60, 80,     // BE
        350, 280, INFI, INFI, INFI, 60, INFI, 60,   // VA
        320, 250, INFI, INFI, 240, 80, 60, INFI     // VI
    };

    int peso2[VERTICES][VERTICES] = {
        // MA   RO    PA    AM    ZU     BE   VA    VI
        INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, // MA
        INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, // MA
        INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, // MA
        INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, // MA
        INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, // MA
        INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, // MA
        INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, // MA
        INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, // MA
    };

    int peso3[VERTICES][VERTICES] = {
        // MA   RO    PA    AM    ZU     BE   VA    VI
        INFI, 1000, INFI, INFI, INFI, INFI, INFI, 1000, // MA
        1000, INFI, 1000, INFI, INFI, INFI, INFI, INFI, // RO
        INFI, 1000, INFI, 1000, INFI, INFI, INFI, INFI, // PA
        INFI, INFI, 1000, INFI, 1000, INFI, INFI, INFI, // AM
        INFI, INFI, INFI, 1000, INFI, 1000, INFI, INFI, // ZU
        INFI, INFI, INFI, INFI, 1000, INFI, 1000, INFI, // BE
        INFI, INFI, INFI, INFI, INFI, 1000, INFI, 1000, // VA
        1000, INFI, INFI, INFI, INFI, INFI, 1000, INFI, // VI
    };
    
    // creamos grafo
    Grafo grafo = Grafo(VERTICES);
    convertirGrafo(peso3, &grafo);

    ArbolM<int> caminos = grafo.buscarCiclosHam(MA);
    caminos.Recorrer();
    caminos.RecorrerH();

    return 0;
}

/**
 * @brief convertirGrafo: convierte una matriz de adyacencia en un grafo
 *
 * @param    M                   Matriz de adyacencia
 * @param    grafo               Grafo a cargar
 */
void convertirGrafo(int M[VERTICES][VERTICES], Grafo *grafo)
{
    for (int j = 0; j < VERTICES; j++)
    {
        for (int i = 0; i < VERTICES; i++)
        {
            if (M[j][i] != INFI)
            {
                grafo->addArista(j, i, M[j][i]);
            }
        }
    }
}
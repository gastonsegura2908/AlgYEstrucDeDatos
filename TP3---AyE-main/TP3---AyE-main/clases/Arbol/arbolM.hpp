#pragma once
#ifndef ARBOLM_H
#define ARBOLM_H
#include "../Lista/lista.hpp"
#include "../Cola/cola.hpp"
#include "../Nodo/nodoA.hpp"

int X = 0;
int COSTO_OPTIMO = 99999999;
string RECORRIDO_OPTIMO = "";
string CODIFICACION[8] = {"MA", "RO", "PA", "AM", "ZU", "BE", "VA", "VI"};

template <class T>
class ArbolM
{
private:
    nodo<T> *raiz;
    void recorrer(nodo<T> *aux, int prof = 0);
    void recorrerH(nodo<T> *aux, Cola<string> *cola, bool show = false);

public:
    ArbolM()
    {
        raiz = NULL;
    };
    ~ArbolM() { delete raiz; };
    void setRaiz(nodo<T> *n) { raiz = n; };
    void Recorrer() { recorrer(raiz); }                           // recorre todos los elementos y los imprime
    void RecorrerH() { recorrerH(raiz, new Cola<string>, true); } // recorre todos los elementos y los imprime
};

/**
 * @brief Recorre todo el arbol m-ario e imprime los datos de cada nodo
 *
 * @tparam T
 * @param aux - nodo auxiliar
 */
template <class T>
void ArbolM<T>::recorrer(nodo<T> *aux, int prof)
{
    if (aux == NULL)
        return;

    for (int i = 0; i < prof; i++)
        cout << "- ";

    cout << CODIFICACION[aux->info] << endl;

    Lista<nodo<T> *> *hijos_copy = aux->hijos->copy();
    hijos_copy->invertir();
    while (true)
    {
        nodo<T> *next = hijos_copy->pop();
        if (next == NULL)
            break;
        recorrer(next, prof + 1);
    }
    delete hijos_copy;
}

/**
 * @brief Recorre todo el arbol m-ario e imprime los datos de cada nodo
 *
 * @tparam T
 * @param aux - nodo auxiliar
 */
template <class T>
void ArbolM<T>::recorrerH(nodo<T> *aux, Cola<string> *cola, bool show)
{
    if (aux == NULL)
        return;

    string ciudad = CODIFICACION[aux->info];

    cola->encolar(ciudad);

    if (aux->hijos->esvacia())
        // es una hoja
        if (aux->info == raiz->info && cola->size() > 1)
        {
            cout << X++ << ". ";
            // es un ciclo hamiltoniano
            cola->impre();
            cout << "- costo: " << aux->der->info;
            cout << endl;

            if (aux->der->info <= COSTO_OPTIMO)
            {
                COSTO_OPTIMO = aux->der->info;
                RECORRIDO_OPTIMO = cola->cola_to_string();
            }
        }

    Lista<nodo<T> *> *hijos_copy = aux->hijos->copy();
    hijos_copy->invertir();
    while (true)
    {
        nodo<T> *next = hijos_copy->pop();
        if (next == NULL)
            break;
        recorrerH(next, cola);
    }
    delete hijos_copy;
    cola->borrar();

    if (show)
    {
        if (RECORRIDO_OPTIMO == "")
        {
            cout << "\nNO EXISTE RECORRIDO VALIDO" << endl;
            return;
        }
        cout << "\nRECORRIDO OPTIMO" << endl;
        cout << RECORRIDO_OPTIMO << "- " << COSTO_OPTIMO << endl;
    }

    return;
}

#endif
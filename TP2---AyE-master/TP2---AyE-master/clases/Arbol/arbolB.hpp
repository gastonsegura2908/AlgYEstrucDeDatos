#pragma once
#ifndef ARBOL_H
#define ARBOL_H
#include "./arbolM.hpp"
#include "../Nodo/nodoA.hpp"

template <class T>
class ArbolB
{
private:
    nodo<T> *raiz, *q;
    void rid(nodo<T> *aux); // recorrido preorden
    void mh(nodo<T> *aux);
    void pasarMaB(nodo<T> *p);
    void pasarMaBOrdenado(nodo<T> *p, string llave, bool es_numero);

public:
    ArbolB()
    {
        raiz = NULL;
    };
    ArbolB(ArbolM *p)
    {
        int *pos;
        *pos = 0;
        bool set_raiz = true;
        PasarMaB(p, pos);
    };
    ~ArbolB(){};
    void PasarMaB(ArbolM *p)
    {
        pasarMaB(p->getRaiz());
        raiz = p->getRaiz();
    };
    void PasarMaBOrdenado(ArbolM *p, string llave, bool es_numero)
    {
        pasarMaBOrdenado(p->getRaiz(), llave, es_numero);
        raiz = p->getRaiz();
    };
    void RID() { rid(raiz); } // recorrido preorden
    void MostrarHojas() { mh(raiz); }
    void agregarOrdenado(nodo<string> *izq, nodo<string> *in, string llave, bool es_numero);
};

/**
 * @brief Pasa un Arbol M-ario a su representacion en arbol Binario
 *
 * @tparam T
 * @param    p - nodo del arbol m-ario (en primera iteracion = raiz)
 */
template <class T>
void ArbolB<T>::pasarMaB(nodo<T> *p)
{
    Lista<nodo<string> *> *hijos_copy = p->hijos->copy();

    if (hijos_copy->esvacia()) // estoy en una hoja o arbol vacio no hago nada
    {
        p->der = NULL;
        p->izq = NULL;
        return;
    }

    while (!hijos_copy->esvacia())
        pasarMaB(hijos_copy->pop()); // ir llamando para ordenar los hijos

    hijos_copy = p->hijos->copy();

    p->izq = hijos_copy->pop(); // seteamos el hijo izquierdo
    p->der = NULL;              // el nodo padre setea el hijo derecho del nodo

    nodo<string> *h1 = p->izq;

    while (!hijos_copy->esvacia())
    {
        h1->der = hijos_copy->pop();
        h1 = h1->der; // asignamos como hijo derecho al hermano derecho
    }

    // no se borra h1 porque nos estaria afectando nuestro arbol despues

    delete hijos_copy;
    hijos_copy = NULL;
}

/**
 * @brief Pasa un arbol M-ario a su representacion Binaria ordenando los datos
 *
 * @tparam T
 * @param    p - nodo del arbol m-ario (en primera iteracion = raiz)
 * @param    llave - llave a usar en las comparaciones
 * @param    es_numero - si el dato a comparar es un numero
 */
template <class T>
void ArbolB<T>::pasarMaBOrdenado(nodo<T> *p, string llave, bool es_numero)
{
    Lista<nodo<string> *> *hijos_copy = p->hijos->copy();

    if (hijos_copy->esvacia()) // estoy en una hoja o arbol vacio no hago nada
    {
        p->der = NULL;
        p->izq = NULL;
        return;
    }

    while (!hijos_copy->esvacia())
        pasarMaBOrdenado(hijos_copy->pop(), llave, es_numero); // ir llamando para ordenar los hijos

    hijos_copy = p->hijos->copy();

    p->izq = hijos_copy->pop(); // seteamos el hijo izquierdo
    p->der = NULL;              // el nodo padre setea el hijo derecho del nodo

    nodo<string> *h1 = p->izq;

    while (!hijos_copy->esvacia())
    {
        if (p->info == "laureates")
        {
            agregarOrdenado(p->izq, hijos_copy->pop(), llave, es_numero);
            continue;
        }
        h1->der = hijos_copy->pop();
        h1 = h1->der; // asignamos como hijo derecho al hermano derecho
    }

    // no se borra h1 porque nos estaria afectando nuestro arbol despues

    delete hijos_copy;
    hijos_copy = NULL;
}

/**
 * @brief Agrega un nodo al arbol binario ordenado
 *
 * @param    izq - Nodo hermano izq
 * @param    in - nodo a agregar
 */
template <class T>
void ArbolB<T>::agregarOrdenado(nodo<string> *izq, nodo<string> *in, string llave, bool es_numero)
{
    if (mayor(izq, in, llave, es_numero))
    {
        swap(*izq, *in);
        izq->der = in; // izq ahora es in e in ahora es izq
        return;
    }

    if (izq->der == NULL)
    {
        // sin hermanos derechos,
        izq->der = in;
        return;
    }

    // comparar con el siguiente hermano
    agregarOrdenado(izq->der, in, llave, es_numero);
}

template <class T>
void ArbolB<T>::rid(nodo<T> *aux)
{
    if (aux != NULL)
    {
        cout << "\n"
             << aux->info;
        if (aux->info == "firstname")
        {
            rid(aux->izq);
            cout << "\n---------" << endl;
            return;
        }

        rid(aux->izq);
        rid(aux->der);
    }
}

template <class T>
void ArbolB<T>::mh(nodo<T> *aux)
{
    if (aux != NULL)
    {
        mh(aux->izq);
        if (aux->izq == NULL && aux->der == NULL)
            cout << "\n"
                 << aux->info;
        mh(aux->der);
    }
}

#endif
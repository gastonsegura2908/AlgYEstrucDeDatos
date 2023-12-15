#pragma once
#ifndef COLA_H
#define COLA_H
#include "../Lista/lista.hpp"

template <class T>
class Cola : public Lista<T>
{
public:
    Cola(void) { Lista<T>(); };
    Cola(Lista<T> *lista)
    {
        Cola();
        this->concat(lista);
    };
    //~Cola(void);
    T tope() { return this->last(); };
    T pop()
    {
        T tope = this->tope();
        this->desencolar();
        return tope;
    };
    bool colavacia(void) { return this->esvacia(); };
    void encolar(T a) { this->add(a); };
    void desencolar(void) { this->borrar_last(); };
    T ultimo(void) { return this->cabeza(); };
    void impre(void)
    {
        Lista<T> *copia = this->copy();
        while (!copia->esvacia())
        {
            cout << copia->last() << " ";
            copia->borrar_last();
        }
    };
    string cola_to_string(void)
    {
        string s = "";
        Lista<T> *copia = this->copy();
        while (!copia->esvacia())
        {
            s += copia->last() + " ";
            copia->borrar_last();
        }
        return s;
    };
    T *colaToArray()
    {
        T *array;
        int len = this->size();
        array = (T *)malloc(sizeof(T) * len); // array de tipo T de size len

        Nodo<T> nodo_lista = this->getNodo(len - 1);
        for (int i = 0; i < len; i++)
        {
            *(array + i) = nodo_lista.get_dato();
            if (i < len - 1)
                nodo_lista = *nodo_lista.get_prev();
        }
        return array;
    }
};

#endif
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
            cout << copia->last() << endl;
            copia->borrar_last();
        }
    };
};

#endif
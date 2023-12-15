#pragma once
#ifndef NODO_H
#define NODO_H
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;
template <class T>
class Nodo
{
private:
    T dato;
    Nodo *next;
    Nodo *prev;

public:
    Nodo()
    {
        next = NULL;
        prev = NULL;
    };
    // al eliminar un nodo no hay que borrar next (liberar memoria) porque sino se
    //  eliminan todos los nodos de la lista
    ~Nodo(){};
    Nodo(T a)
    {
        dato = a;
        next = NULL;
        prev = NULL;
    };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo *n) { next = n; };
    void set_prev(Nodo *n) { prev = n; };
    T get_dato() { return dato; };
    Nodo *get_next() { return next; };
    Nodo *get_prev() { return prev; };
    bool es_vacio() { return next == NULL; }
};

#endif
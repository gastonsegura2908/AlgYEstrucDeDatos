#pragma once
#ifndef NODOA_H
#define NODOA_H

#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;
template <class T>
class nodo
{
public:
    T info;                                         // dato
    nodo *der, *izq, *padre;                        // para arbol binario
    Lista<nodo<T> *> *hijos = new Lista<nodo<T> *>; // para arbol m-ario
    ~nodo(){};                                      // destructor vacio para no borrar todo el arbol al borrar un nodo
    nodo(){};
    nodo(T dato) { info = dato; };
};
#endif

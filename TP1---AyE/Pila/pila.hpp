#pragma once
#ifndef PILA_H
#define PILA_H
#include "../Lista/lista.hpp"

using namespace std;

template <class T>
class Pila : public Lista<T>
{
public:
      Pila() { Lista<T>(); };
      Pila(Lista<T> *l)
      {
            Pila();
            this->concat(l);
      };
      void apilar(T d) { this->add(d); };
      T tope(void) { return this->cabeza(); };
      T pop(void)
      {
            T tope = this->tope();
            this->desapilar();
            return tope;
      };
      void desapilar(void) { this->borrar(); };
      bool pilavacia() { return this->esvacia(); };
};

#endif
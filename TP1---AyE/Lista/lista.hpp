#pragma once
#ifndef LISTA_H
#define LISTA_H
#include "../Nodo/nodo.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class Lista
{
private:
    Nodo<T> *czo;
    void borrarD(T d, Nodo<T> *ant);

public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T> *n) { czo = n; };
    Lista(Lista<T> *l)
    {
        czo = new Nodo<T>();
        this->concat(l);
    }
    ~Lista()
    {
        while (!esvacia())
        {
            borrar();
        }
    };
    void add(T d); // sumar nodos a la lista
    bool esvacia(void);
    T cabeza(void);     // retorna el dato del primer nodo
    Lista *resto(void); // retorna el puntero al "resto" de la lista sin la cabeza
    void impre(void);
    int size();
    bool esta(T d);
    void borrarDato(T d) { borrarD(d, NULL); } // borra el nodo que contiene d
    void borrar(void);                         // borra la cabeza
    void borrar_last();                        // borra el ultimo
    void concat(Lista<T> *l1);                 // le transfiere los datos de l1 a this
    Lista<T> *copy(void);                      // hace una copia de la lista
    void tomar(int n);                         // deja "vivos" los n primeros nodos y borra el resto
    void final(int n);                         // deja "vivos" a partir del n nodo y borra el resto
    void slice(int start, int end);            // deja "vivos" a partir del nodo start hasta el end y borra el resto
    T last();                                  // retorna el dato del ultimo nodo
    int buscar(T dato, int pos = -1);          // busca el dato y retorna su posicion
    T get(int pos);                            // devuelve el elemento de la posicion
    void invertir();                           // invierte el orden de todos los elementos de la lista
    void reemplazar(int n, T dato);            // reemplaza el dato de la posicion n
};

/**
 * @brief Reemplaza el dato del nodo n
 *
 * @tparam T
 * @param    n - posicion del nodo a reemplazar
 * @param    dato - nuevo dato
 */
template <class T>
void Lista<T>::reemplazar(int n, T dato)
{
    if (n < 0 || n > this->size() - 1)
        return;

    if (n == 0)
    {
        czo->set_dato(dato);
        return;
    }

    this->resto()->reemplazar(n - 1, dato);
}

/**
 * @brief Invierte el orden de la lista
 *
 * @tparam T
 */
template <class T>
void Lista<T>::invertir()
{
    int len = this->size();
    Lista<T> *nueva = new Lista<T>();
    for (int i = 0; i < len; i++)
    {
        nueva->add(this->cabeza());
        this->borrar();
    }
    czo = nueva->czo;
}

/**
 * @brief Slice corta la lista entre dos valores
 * @param start - a partir de que nodo tomar
 * @param end - hasta que nodo tomar, sin incluir
 * @return void, se modifica la lista actual
 */
template <class T>
void Lista<T>::slice(int start, int end)
{
    tomar(end);
    final(start);
}

/**
 * @brief Final deja "vivos" a partir del n nodo y borra el resto
 *
 * @param n - Hasta que nodo eliminar
 */
template <class T>
void Lista<T>::final(int n)
{
    if (n <= 0 || esvacia())
        return;
    borrar();
    final(n - 1);
}

/**
 * @brief Devuelve el dato del elemento en cierta posicion
 *
 * @tparam T
 * @param    pos - posicion del elemento a tomar
 * @return T
 */
template <class T>
T Lista<T>::get(int pos)
{
    if (pos < 0 || pos > this->size() - 1)
        return T();

    if (pos == 0)
        return this->cabeza();

    return this->resto()->get(pos - 1);
}

/**
 * @brief Busca un dato y devuelve su posicion
 *
 * @param    dato - dato a buscar en la lista
 * @return int - posicion del elemento a buscar, -1 si no se encuentra
 */
template <class T>
int Lista<T>::buscar(T dato, int pos)
{
    if (this->esvacia())
        return -1;

    pos++;
    if (this->cabeza() == dato)
        return pos;

    return this->resto()->buscar(dato, pos);
}

/**
 * @brief Last devuelve el elemento en la ultima posicion
 *
 * @tparam T
 * @return T
 */
template <class T>
T Lista<T>::last()
{
    if (!this->esvacia())
    {
        if (this->resto()->esvacia())
            return this->cabeza();
        return this->resto()->last();
    }
    return 0;
}

/**
 * @brief Add agrega un elemento a la lista
 *
 * @tparam T
 * @param    d - Elemento a agregar
 */
template <class T>
void Lista<T>::add(T d) // 100
{
    Nodo<T> *nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}

/**
 * @brief Esvacia devuelve si la lista es vacia
 *
 * @tparam T
 * @return bool, true si es vacia false caso contrario
 */
template <class T>
bool Lista<T>::esvacia(void)
{
    return czo->es_vacio();
}

/**
 * @brief Devuelve el dato de la cabeza de la lista
 *
 * @tparam T
 * @return T
 */
template <class T>
T Lista<T>::cabeza(void)
{
    if (this->esvacia())
    {
        // cout << " Error, Cabeza de lista vacia" << endl;
        return T();
    }
    return czo->get_dato();
}

/**
 * @brief Crea una nueva lista sin la cabeza
 *
 * @tparam T
 * @return Lista<T>* - resto de la lista
 */
template <class T>
Lista<T> *Lista<T>::resto(void)
{
    Lista *l = new Lista(czo->get_next());
    return (l);
}

/**
 * @brief Calcula la cantidad de elementos de la lista
 *
 * @return int
 */
template <class T>
int Lista<T>::size()
{
    if (this->esvacia())
        return 0;
    return 1 + this->resto()->size();
}

/**
 * @brief Borra la cabeza de la lista
 *
 */
template <class T>
void Lista<T>::borrar(void)
{ // borra el nodo cabeza
    if (!this->esvacia())
    {
        Nodo<T> *tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

/**
 * @brief Borra el ultimo elemento
 */
template <class T>
void Lista<T>::borrar_last()
{ // borra el ultimo nodo
    if (!this->esvacia())
    {
        if ((czo->get_next())->get_next() == NULL)
        {
            delete czo->get_next();
            czo->set_next(NULL);
        }
        else
            this->resto()->borrar_last();
    }
}

/**
 * @brief Concatena 2 listas, transfiere los datos de l1 a this
 * Los elementos de l1 se agregan en orden encima de los elementos de la lista
 * @param    l1 - lista a concatenar
 */
template <class T>
void Lista<T>::concat(Lista<T> *l1)
{ // le transfiere los datos de l1 a this
    if (!(l1->esvacia()))
    {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}

/**
 * @brief Crea una copia de la lista
 *
 * @return Lista<T>*
 */
template <class T>
Lista<T> *Lista<T>::copy(void)
{
    Lista<T> *aux = new Lista();
    aux->concat(this);
    return aux;
}

/**
 * @brief Tomar deja "vivos" los n primeros nodos y borra el resto
 *
 * @param    n - cantidad de elementos a guardar
 */
template <class T>
void Lista<T>::tomar(int n)
{ // deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n)
    {
        this->borrar_last();
        this->tomar(n);
    }
}

template <class T>
void Lista<T>::impre(void)
{
    Nodo<T> *aux;
    aux = czo;
    while (aux->get_next() != NULL)
    {
        cout << aux->get_dato() << endl;
        aux = aux->get_next();
    }
}

/**
 * @brief Se fija si existe el dato en la lista
 *
 * @param    d - Dato a buscar
 * @return true si existe, false c.c.
 */
template <class T>
bool Lista<T>::esta(T d)
{ // busca d en la lista
    if (this->esvacia())
        return false;
    if (this->cabeza() == d)
        return true;

    return this->resto()->esta(d);
}

template <class T>
void Lista<T>::borrarD(T d, Nodo<T> *ant)
{
    if (!this->esvacia())
    {
        if (d == this->cabeza())
        {
            if (ant == NULL)
            { // al principio
                this->borrar();
            }
            else
            { // entre medio
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else
            this->resto()->borrarD(d, czo);
    }
}

#endif
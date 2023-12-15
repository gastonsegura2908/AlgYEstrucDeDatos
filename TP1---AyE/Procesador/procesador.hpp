#pragma once
#ifndef PROCESADOR_H
#define PROCESADOR_H
#include "../Instruccion/instruccion.hpp"
#include "../Calculadora/calculadora.hpp"
#include "../Instruccion/Declaracion/declaracion.hpp"
#include "../Instruccion/Condicional/condicional.hpp"
#include "../Instruccion/Jump/jump.hpp"
#include "../Instruccion/Show/show.hpp"
#include "../Instruccion/Asignacion/asignacion.hpp"

class Procesador
{
public:
    static Lista<Instruccion *> *compilar(Pila<string> *l);

    static void procesar(Lista<Instruccion *> *instrucciones);

    static Instruccion *crear_instruccion(string s);
};

/**
 * @brief Preprocesa la lista de strings en una lista de instrucciones
 * @param l - lista de instrucciones como strings
 * @return Lista<Instruccion*>
 */
Lista<Instruccion *> *Procesador::compilar(Pila<string> *l)
{
    Lista<Instruccion *> *instrucciones = new Lista<Instruccion *>();
    while (!l->esvacia())
    {
        string in_string = l->pop(); // saco string de la pila

        Instruccion *nueva = crear_instruccion(in_string);

        if (nueva->getInstruccion().size() == 0)
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Instruccion no reconocida";
            delete instrucciones, nueva;
            exit(1);
        }

        instrucciones->add(nueva);
    }

    instrucciones->invertir();
    return instrucciones;
}

/**
 * @brief Ejecuta una lista de instrucciones
 * @param instrucciones
 */
void Procesador::procesar(Lista<Instruccion *> *instrucciones)
{
    int len = instrucciones->size();                   // cantidad de instrucciones
    Lista<Variable *> *vars = new Lista<Variable *>(); // lista de variables del programa
    for (int i = 0; i < len; i++)
    {
        // cout << "Instruccion: " << i + 1 << " . " << instrucciones->get(i)->getInstruccion() << endl;
        instrucciones->get(i)->ejecutar(vars, &i);
    }

    // Liberar Memoria
    delete vars;
}

/**
 * @brief Crea una instruccion de la subclase requrida
 *
 * @param    s - string de la instruccion
 * @return Instruccion*
 */
Instruccion *Procesador::crear_instruccion(string s)
{
    Lista<string> in_lista = *Calculadora::string_a_lista(s); // lo convierto a una lista
    string p1 = in_lista.get(0);                              // obtengo la primera palabra

    Instruccion *nueva;

    if (p1 == "INT" || p1 == "BOOL")
    {
        nueva = new Declaracion(s); // crear Declaracion
    }
    else if (p1 == "JUMP")
    {
        nueva = new Jump(s); // crear Jump
    }
    else if (p1 == "IF")
    {
        nueva = new Condicional(s); // crear Condicional
    }
    else if (p1 == "SHOW")
    {
        nueva = new Show(s); // crear Show
    }
    else if (in_lista.get(1) == "=")
    {
        nueva = new Asignacion(s); // crear Asignacion
    }
    else
    {
        std::cerr << "Ocurrio un error" << endl;
        std::cerr << "Instruccion no identificada: " << s << endl;
        delete nueva;
        exit(1);
    }

    return nueva;
}

#endif
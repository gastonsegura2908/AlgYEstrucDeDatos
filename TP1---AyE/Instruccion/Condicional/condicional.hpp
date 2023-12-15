#pragma once
#ifndef CONDICIONAL_H
#define CONDICIONAL_H

#include "../Declaracion/declaracion.hpp"
#include "../Jump/jump.hpp"
#include "../Show/show.hpp"
#include "../Asignacion/asignacion.hpp"

/**
 * @brief Modela una instruccion condicional que evalua una
 * expresion logica y ejecuta una nueva instruccion
 */
class Condicional : public Instruccion
{
private:
    string cond;          // expresion aritmetica condicional
    string cond_postfija; // expresion aritmetica condicional
    Instruccion *then;

public:
    Condicional(string s)
    {
        this->setInstruccion(s);
        parsearCondicional(s);
    };
    ~Condicional()
    {
        delete then;
    }
    void parsearCondicional(string s)
    {
        // usar metodo string a lista obtener las condiciones entre los parentesis

        Lista<string> *lista = Calculadora::string_a_lista(s);
        Lista<string> *condicion = lista->copy();

        condicion->slice(lista->buscar("(") + 1, lista->buscar(")"));

        if (condicion->esvacia() || condicion->size() == lista->size())
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Condicion Invalida: " << s << endl;
            delete lista, condicion; // libera espacio
            exit(1);
        }

        // calcular expresion postfija

        cond = Calculadora::lista_a_string(condicion);

        if (!validar_aritmetica(cond))
        {
            // aritmetica invalida
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Condicion Invalida: " << s << endl;
            delete lista, condicion; // libera espacio
            exit(1);
        }

        cond_postfija = Calculadora::string_a_postfijo(cond);

        // crear la instruccion correspondiente que sigue del then

        Lista<string> *siguiente = lista->copy();
        siguiente->slice(lista->buscar("THEN") + 1, lista->size());

        if (siguiente->esvacia() || siguiente->size() == lista->size())
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Expresion THEN Invalida: " << s << endl;
            delete lista, condicion, siguiente; // libera espacio
            exit(1);
        }

        then = crear_instruccion(Calculadora::lista_a_string(siguiente));

        if (then->getInstruccion().size() == 0)
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Expresion THEN Invalida: " << s << endl;
            delete lista, condicion, siguiente; // libera espacio
            exit(1);
        }
        delete lista, condicion, siguiente; // libera espacio
    }

    /**
     * @brief Al ejecutar un condicional se evalua una expresion
     * logica y en caso de ser verdadera se ejecuta la instruccion siguiente
     *
     * @param    vars - Lista de Variables
     */
    virtual void exec(Lista<Variable *> *vars, int *linea_actual) override
    {
        // hacer la aritmetica de la condicion
        bool res;

        try
        {
            res = Calculadora::calcular(cond_postfija, vars);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Ocurrio un error: linea - " << 1 + *linea_actual << endl;
            std::cerr << "Expresion aritmetica invalida: " << cond << endl;
            exit(1); // terminamos el programa
        }

        // si se cumple la condicion aritmetica, ejecutar instruccion then
        if (res)
            then->ejecutar(vars, linea_actual);
    };

    Instruccion *crear_instruccion(string s);
};

Instruccion *Condicional::crear_instruccion(string s)
{
    Lista<string> in_lista = *Calculadora::string_a_lista(s); // lo convierto a una lista
    string p1 = in_lista.get(0);                              // obtengo la primera palabra

    Instruccion *nueva;

    if (p1 == "INT" || p1 == "BOOL")
        nueva = new Declaracion(s); // crear Declaracion
    else if (p1 == "JUMP")
        nueva = new Jump(s); // crear Jump
    else if (p1 == "IF")
        nueva = new Condicional(s); // crear Condicional
    else if (p1 == "SHOW")
        nueva = new Show(s); // crear Show
    else if (in_lista.get(1) == "=")
        nueva = new Asignacion(s); // crear Asignacion
    else
    {
        cout << "Instruccion no identificada: " << s << endl;
        return new Instruccion();
    }
    return nueva;
};

#endif
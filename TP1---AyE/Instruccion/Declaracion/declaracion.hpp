#pragma once
#ifndef DECLARACION_H
#define DECLARACION_H

#include "../instruccion.hpp"

/**
 * @brief Modela una instruccion de declaracion
 * Las variables pueden ser de tipo INT o BOOL
 */
class Declaracion : public Instruccion
{
private:
    Variable *val; // objeto creado en la declaracion

public:
    Declaracion(string s) // constructor
    {
        this->setInstruccion(s);
        parseDeclaracion(s); // reserva el lugar para la variable y setea TIPO y nombre
    };
    ~Declaracion()
    {
        delete val;
    }

    void parseDeclaracion(string s)
    {
        Lista<string> *parse = Calculadora::string_a_lista(s); // separa la string en espacios y crea una lista

        if (parse->size() != 2)
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Cantidad de terminos erronea (!=2) en declaracion " << s << endl;
            delete parse; // libera espacio
            exit(1);
        }

        string nom = parse->get(1);

        if ((nom.size()) != 1) // chequeo que haya un solo caracter como nombre
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Nombre de Variable Invalido: " << s << " Uso (a=<x<=z) y solo un caracter" << endl;
            delete parse; // libera espacio
            exit(1);
        }

        char name = nom[0]; // transforma de string a char

        if (parse->get(0) == "INT") // chequeo si variable a declarar es INT
        {
            val = new Variable(name, INT); // crea el objeto de la clase variable(INT) y lo apunta con val
        }
        else
        {
            val = new Variable(name, BOOL); // crea el objeto de la clase variable(BOOL) y lo apunta con val
        }
        delete parse; // libera espacio
    };

    Variable *get_Variable()
    {
        return val;
    };

    /**
     * @brief Al ejecutar una declaracion se agrega una variable a la
     * lista de variables si previamente no habia sido declarada
     *
     * @param    vars - Lista de variables
     */
    virtual void exec(Lista<Variable *> *vars, int *linea_actual) override // Lista<Variables> *l
    {
        char nom_nueva = val->getName(); // guarda el nombre de la variable que se quiere agregar a la lista

        int len = vars->size();

        // recorre la lista de variables
        for (int i = 0; i < len; i++)
        {
            char nom_i = vars->get(i)->getName(); // guarda el nombre de la variable actual

            if (nom_i == nom_nueva) // compara
            {
                // ya esta declarada
                std::cerr << "Ocurrio un error: linea - " << 1 + *linea_actual << endl;
                std::cerr << "la variable " << nom_i << " ya fue declarada con anterioridad" << endl;
                exit(1);
            }
        }

        // si no hubo coincidencias agrega la variable a la lista
        vars->add(val);
    };
};

#endif

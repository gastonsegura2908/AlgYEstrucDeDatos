#pragma once
#ifndef ASIGNACION_H
#define ASIGNACION_H

#include "../instruccion.hpp"
/**
 * @brief Modela una instruccion de asignacion
 * Al ejecutar una asignacion se calcula una expresion aritmetica y se
 * agrega el valor a su variable
 */

class Asignacion : public Instruccion
{
private:
    string ex;
    string ex_postfija;
    char var_name;

public:
    Asignacion(string s)
    {
        this->setInstruccion(s); // instruccion es de la clase instruccion
        parsearAsignacion(s);
    };

    string getEx()
    {
        return ex;
    }

    string getExPos()
    {
        return ex_postfija;
    }

    char getName()
    {
        return var_name;
    }

    void parsearAsignacion(string s)
    {
        Lista<string> *parse = Calculadora::string_a_lista(s); // parsea la string y convierte a lista separada por espacios
        string e1 = parse->get(0);                             // toma el primer elemento de la lista

        if (e1.size() != 1 || !Calculadora::es_minus(e1[0]))
        {
            std::cerr << "Ocurrio un error: " << endl;
            std::cerr << "Asignacion Invalida (NV)" << s << endl;

            // libera espacio
            delete parse;

            exit(1);
        }

        string e2 = parse->get(1); // toma el segundo elemento de la lista

        if (e2.size() != 1 || e2[0] != '=') // se verifica si es '='
        {
            std::cerr << "Ocurrio un error: " << endl;
            std::cerr << "Asignacion Invalida (=)" << s << endl;

            // libera espacio
            delete parse;

            exit(1);
        }

        Lista<string> *parse_copy = parse->copy(); // copia la lista parseada
        parse_copy->final(2);                      // tomamos la lista a partir del igual

        string aritmetica = Calculadora::lista_a_string(parse_copy); // convertimos a string

        if (!validar_aritmetica(aritmetica))
        {
            std::cerr << "Ocurrio un error: " << endl;
            std::cerr << "Asignacion Invalida (aritmetica)" << s << endl;

            // libera espacio
            delete parse, parse_copy;
            exit(1);
        }

        // agarro la expresion porque esta correcta

        ex = aritmetica;                                          // guardamos la expresion aritmetica
        ex_postfija = Calculadora::string_a_postfijo(aritmetica); // guardamos la expresion postfija
        var_name = e1[0];                                         // guardamos el valor de la variable pendiente a asignar
        delete parse, parse_copy;                                 // libera espacio
    }

    /**
     * @brief Al ejecutar la asignacion se calcula la expresion aritmetica posfija
     * y se asigna su resultado a su valor
     *
     * @param    vars - Lista de variables
     */
    virtual void exec(Lista<Variable *> *vars, int *linea_actual) override
    {
        // calcular expresion aritmetica
        int res;
        try
        {
            res = Calculadora::calcular(ex_postfija, vars);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Ocurrio un error: linea - " << 1 + *linea_actual << endl;
            std::cerr << "Expresion aritmetica invalida: " << ex << endl;
            exit(1); // terminamos el programa
        }
        int len = vars->size();

        // recorre la lista de variables
        for (int i = 0; i < len; i++)
        {
            char nom_i = vars->get(i)->getName(); // guarda el nombre de la variable actual

            if (nom_i == var_name) // compara si existe y setea el valor de la variable
            {
                vars->get(i)->setValor(res);
                return;
            }
        }

        std::cerr << "Ocurrio un error: linea - " << 1 + *linea_actual;
        std::cerr << "Variable " << var_name << " no fue declarada!" << endl;
        exit(1);
    };
};

#endif

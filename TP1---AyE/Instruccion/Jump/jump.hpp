#pragma once
#ifndef JUMP_H
#define JUMP_H

#include "../instruccion.hpp"

/**
 * @brief Modela una instruccion Jump
 * al ejecutarse salta a una instruccion anterior o posterior
 */
class Jump : public Instruccion
{
private:
    string ex; // expresion aritmetica a evaluar
    string ex_postfija;

public:
    Jump(string s)
    {
        this->setInstruccion(s);
        parsearJump(s);
    };

    void parsearJump(string s)
    {
        // parsear string a lista
        Lista<string> *lista = Calculadora::string_a_lista(s);
        Lista<string> *ex_l = lista->copy();

        // obtener expresion del jump
        // "JUMP ......"
        ex_l->slice(1, lista->size());

        ex = Calculadora::lista_a_string(ex_l);

        if (!validar_aritmetica(ex))
        {
            // expresion invalida
            std::cerr << "Ocurrio un error" << endl;
            cout << "Expresion Invalida JUMP: " << s << endl;
            delete lista, ex_l; // libera espacio
            exit(1);
        }
        // convierto la expresion a postfija

        ex_postfija = Calculadora::string_a_postfijo(ex);
        delete lista, ex_l; // libera espacio
    };

    /**
     * @brief Al ejecutar un Jump se salta a una instruccion anterior o posterior
     *
     * @param    vars - Lista de Variables
     * @param    instrucciones - Lista de Punteros a Instrucciones
     * @param    linea_actual - Linea actual de ejecucion (Instruccion actual)
     */
    virtual void exec(Lista<Variable *> *vars, int *linea_actual) override
    {
        int nueva_linea;

        try
        {
            nueva_linea = Calculadora::calcular(ex_postfija, vars);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Ocurrio un error: linea - " << 1 + *linea_actual << endl;
            std::cerr << "Expresion aritmetica invalida: " << ex << endl;
            exit(1); // terminamos el programa
        }

        if (nueva_linea < 1)
        {
            // no se puede ir a una linea menor a 0
            std::cerr << "Ocurrio un error: linea - " << 1 + *linea_actual << endl;
            std::cerr << "expresion invalida: " << this->getInstruccion() << " no puedo saltar como Michael Jordan!";
            exit(1);
        }
        // si se intenta ir a una linea mayor a la ultima, se termina el programa

        // el primer -1 es porque la lista usa 0 index y el segundo es porque el for del procesador le va a sumar uno
        *linea_actual = nueva_linea - 1 - 1;
    };
};

#endif
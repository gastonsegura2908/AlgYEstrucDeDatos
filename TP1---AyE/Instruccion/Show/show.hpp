#pragma once
#ifndef SHOW_H
#define SHOW_H
#include "../instruccion.hpp"

/**
 * @brief Modela un instruccion Show que imprime un resultado por pantalla
 */
class Show : public Instruccion
{
private:
  string ex; // expresion aritmetica a imprimir
  string ex_postfija;

public:
  Show(string s)
  {
    this->setInstruccion(s);
    parsearShow(s);
  };
  void parsearShow(string s)
  {
    // parsear string a lista y obtener la expresion
    Lista<string> *lista = Calculadora::string_a_lista(s);

    lista->slice(lista->buscar("SHOW") + 1, lista->size());

    ex = Calculadora::lista_a_string(lista);

    // validamos expresion aritmetica
    if (!validar_aritmetica(ex))
    {
      std::cerr << "Ocurrio un error" << endl;
      std::cerr << "Expresion Invalida: " << s << endl;
      delete lista; // libera memoria
      exit(1);
    }

    // calcular expresion postfija
    ex_postfija = Calculadora::string_a_postfijo(ex);
    delete lista; // libera memoria
  };

  /**
   * @brief Al ejecutar se calcula una expresion aritmetica y se muestra por pantalla
   *
   * @param    vars - Lista de Variables
   */
  virtual void exec(Lista<Variable *> *vars, int *linea_actual) override
  {
    // evaluar expresion aritmetica e imprimir resultado
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
    cout << res << endl;
  };
};

#endif
#pragma once

#ifndef INSTRUCCION_H
#define INSTRUCCION_H

#include "../Calculadora/calculadora.hpp"

/**
 * @brief Modela una instruccion del programa
 * Hay 5 tipos de instruccion: Declaracion, Asignacion, Condicional, Jump y Show
 * Cada subclase define como se comporta el metodo ejecutar
 */
class Instruccion
{
private:
  string instruccion = "";
  // funcion exec se sobrescribe en cada subclase
  virtual void exec(Lista<Variable *> *vars, int *linea_actual){};

public:
  Instruccion(){};
  void setInstruccion(string s)
  {
    instruccion = s;
  };

  string getInstruccion()
  {
    return instruccion;
  };

  /**
   * @brief Ejecuta la instruccion de acuerdo a su subclase
   *
   * @param    vars - Lista de Variables Declaradas
   * @param    instrucciones - Lista de instrucciones
   * @param    linea_actual - Linea actual de procesamiento (n° de instruccion)
   */
  void ejecutar(Lista<Variable *> *vars, int *linea_actual)
  {
    // desde la lista se llama a esta funcion
    exec(vars, linea_actual);
  };

  bool validar_aritmetica(string ex);
};

/**
 * @brief Valida una expresion aritmetica
 * Condiciones: Nombres de variable con minuscula, solo parentesis, operadores,
 * varaiables o numeros.
 *
 * @param    ex - string con expresion a validar
 * @return bool, true si es valida, false c.c.
 */
bool Instruccion::validar_aritmetica(string ex)
{
  // si es un string vacio devolver false
  if (ex.size() == 0)
  {
    // cout << "ACA SIZE" << endl;
    return false;
  }

  // verificamos si los parentesis estan equilibrados
  if (!Calculadora::es_equilibrada(ex))
  {
    // cout << "ACA equilibrio";
    return false;
  }

  Lista<string> *parse_copy = Calculadora::string_a_lista(ex); // copia la lista parseada                                        // le saca los 2 primeros elementos a la lista
  int len = parse_copy->size();

  // iteramos entre todos los elementos de la lista
  for (int j = 0; j < len; j++)
  {
    string elem = parse_copy->get(j); // extrae elemento de la lista con indice j

    if (elem.size() == 1)
    {
      // elemento de un solo caracter
      // verificamos que sea: + - / * ( ) < > 0-9 a-z
      char c = elem[0];
      // cout << c << endl;

      // elemento invalido -> expresion invalida

      if (!(Calculadora::es_minus(c) || Calculadora::es_numero(c) || Calculadora::es_operador(elem) || c == 41 || c == 40))
      {
        // cout << "Aca esta el problema" << endl;
        delete parse_copy; //libera espacio
        return false;
      }
    }
    else if (elem.size() == 2)
    {
      // elemento de dos caracteres
      // verificar que sea un operador o un numero
      //  56 <= >= == != 5/ a5

      char c = elem[0];
      char c1 = elem[1];

      // si el primer elemento es una minuscula es invalido
      if (Calculadora::es_minus(c))
      {
        // cout << "ACA MINUSCULA" << endl;
        delete parse_copy; //libera espacio
        return false;
      }

      // si el primer elemento es un numero y el 2do no,es invalido
      if (Calculadora::es_numero(c) && !Calculadora::es_numero(c1))
      {
        // cout << "ACA NUMERO" << endl;
        delete parse_copy; //libera espacio
        return false;
      }

      // si el elemento no es un operador y no es un numero, es invalido
      if (!Calculadora::es_numero(c) && !Calculadora::es_operador(elem))
      {
        // cout << "ACA OPERADOR" << endl;
        delete parse_copy; //libera espacio
        return false;
      }
    }
    else if (elem.size() > 2)
    {
      // elemento con mas de 2 caracteres
      // solo puede ser un numero

      // iteramos por cada caracter buscando elementos invalidos
      for (int h = 0; h < elem.size(); h++)
      {
        char c = elem[h];

        // si tiene simbolos distintos de numeros expresion invalida
        if (!Calculadora::es_numero(c))
        {
          // cout << elem << endl;
          // cout << "ACA SIZE > 2" << endl;
          delete parse_copy; //libera espacio
          return false;
        }
      }
    }
  }

  // si no se encontro ningun error
  delete parse_copy; //libera espacio
  return true;
}

#endif
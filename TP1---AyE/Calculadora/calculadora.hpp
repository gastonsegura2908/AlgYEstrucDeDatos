#ifndef CALCULADORA_H
#define CALCULADORA_H

#include "../Pila/pila.hpp"
#include "../Variable/variable.hpp"
class Calculadora
{
private:
    static int get_precedencia(string op);

public:
    Calculadora(){};  // constructor
    ~Calculadora(){}; // Destructor
    static bool es_operador(string op);
    static bool es_numero(char num);
    static bool es_minus(char minus);
    static int calcular(string ex, Lista<Variable *> *vars);
    static Pila<string> *convertir_a_postfija(Lista<string> *l);
    static string string_a_postfijo(string infija);
    static Lista<string> *string_a_lista(string s, string del = " ");
    static string lista_a_string(Lista<string> *l);
    static void reemplazar_variables(Lista<string> *, Lista<Variable *> *);
    static bool es_equilibrada(string cadena);
};

/**
 * @brief Calcula una expresion aritmetica
 *
 * @param    ex - expresion aritmetica
 * @return int
 */
int Calculadora::calcular(string postfija, Lista<Variable *> *vars)
{
    // verificar que sea valida
    // si no es valida (tirar error?)

    Lista<string> *l = string_a_lista(postfija);
    Pila<string> *p1 = new Pila<string>(l); // pila principal con expresion posfija

    reemplazar_variables(p1, vars); // reemplazamos las variables en la expresion postfija

    Pila<string> *aux = new Pila<string>(); // pila auxiliar
    int error = -1;                         // error, -1 -> no hay error, 64 -> error
    int len = p1->size();

    if (len == 2)
    {
        string e1 = p1->pop();
        string e2 = p1->pop();
        if (!es_operador(e2))
        {
            std::cerr << "Ocurrio un Error" << endl;
            std::cerr << "Error aritmetico: " << postfija << endl;
            std::exit(1);
        }

        if (e2 == "-")
            return (-stoi(e1));
        if (e2 == "+")
            return stoi(e1);

        std::cerr << "Ocurrio un Error" << endl;
        std::cerr << "Error aritmetico: " << postfija;
        std::exit(1);
    }

    for (int i = 0; i < len && error != 64; i++)
    {
        string tope = p1->pop();

        // Controlar la si es una operacion y operar en consecuencia
        if (tope == "+")
        {
            aux->apilar(to_string((stoi(aux->pop()) + stoi(aux->pop()))));
            continue;
        }
        if (tope == "-")
        {
            int a1 = stoi(aux->pop());
            int a2 = stoi(aux->pop());
            aux->apilar(to_string(a2 - a1));
            continue;
        }
        if (tope == "/")
        {
            int a1 = stoi(aux->pop());
            int a2 = stoi(aux->pop());
            aux->apilar(to_string(a2 / a1));
            continue;
        }
        if (tope == "*")
        {
            aux->apilar(to_string(stoi(aux->pop()) * stoi(aux->pop())));
            continue;
        }
        if (tope == "==")
        {
            aux->apilar(to_string((stoi(aux->pop()) == stoi(aux->pop()))));
            continue;
        }
        if (tope == "!=")
        {
            aux->apilar(to_string((stoi(aux->pop()) != stoi(aux->pop()))));
            continue;
        }
        if (tope == ">")
        {
            int a1 = stoi(aux->pop());
            int a2 = stoi(aux->pop());
            aux->apilar(to_string(a2 > a1));
            continue;
        }
        if (tope == ">=")
        {
            int a1 = stoi(aux->pop());
            int a2 = stoi(aux->pop());
            aux->apilar(to_string(a2 >= a1));
            continue;
        }
        if (tope == "<")
        {
            int a1 = stoi(aux->pop());
            int a2 = stoi(aux->pop());
            aux->apilar(to_string(a2 < a1));
            continue;
        }
        if (tope == "<=")
        {
            int a1 = stoi(aux->pop());
            int a2 = stoi(aux->pop());
            aux->apilar(to_string(a2 <= a1));
            continue;
        }

        // no es una operacion, entonces almacenar numero en pila auxiliar
        aux->apilar(tope);
    }

    if (!p1->esvacia() || aux->size() != 1)
    {
        // error
        std::cerr << "Ocurrio un error" << endl;
        std::cerr << "Error en la expresion: " << postfija << endl;

        // Limpiamos memoria
        delete l, p1, aux;
        exit(1);
    }

    int res = stoi(aux->tope());

    // Limpiamos memoria
    delete l, p1, aux;

    return res;
}

/**
 * @brief Convierte expresion infija a postfija
 *
 * @param    l - lista con expresion infija
 * @return Pila<string>*
 */
Pila<string> *Calculadora::convertir_a_postfija(Lista<string> *l)
{
    Pila<string> *l1 = new Pila<string>(l);
    int len = l1->size();
    Pila<string> *postfija = new Pila<string>();   // pila resultado
    Pila<string> *operadores = new Pila<string>(); // pila auxiliar para almacenar operadores

    for (int i = 0; i < len; i++)
    {
        string s = l1->pop(); // saco el elemento de arriba de la pila
        if (es_operador(s))
        {
            // desapilo todos los operadores de mayor presedencia y los agrego a la pila resultado
            while (!operadores->esvacia() && get_precedencia(s) <= get_precedencia(operadores->cabeza()))
                postfija->apilar(operadores->pop());

            // agrego s a la pila
            operadores->apilar(s);
        }
        else if (s == "(")
        {
            // los parentesis para abrir se apilan en los operadores
            operadores->apilar(s);
        }
        else if (s == ")")
        {
            // desapilo todos los elementos y los voy apilando en la pila de resultado hasta encontrar un parentesis abierto
            string operador;
            while (!operadores->esvacia() && (operador = operadores->pop()) != "(")
                postfija->apilar(operador);
        }
        else
        {
            // es un numero o variable, se agrega a la pila de resultado
            postfija->apilar(s);
        }
    }

    // apilo operadores restantes
    while (!operadores->esvacia())
        postfija->apilar(operadores->pop());

    postfija->invertir(); // invierto el orden para que los primeros elementos del string queden arriba
    // limpiamos memoria
    delete l1, operadores;
    return postfija;
}

/**
 * @brief Calcula la expresion postfija de una expresion infija
 *
 * @param    infija - string con expresion infija
 * @return string con expresion postfija
 */
string Calculadora::string_a_postfijo(string infija)
{
    return lista_a_string(convertir_a_postfija(string_a_lista(infija)));
}

/**
 * @brief Crea una lista a partir de un string
 *
 * @param    s - String a parsear
 * @param    del - separador de palabras, " " predeterminado
 * @return Lista<string>*
 */
Lista<string> *Calculadora::string_a_lista(string s, string del)
{
    Lista<string> *p = new Lista<string>();
    int start = 0;
    int end = s.find(del);
    while (end != -1)
    {
        p->add(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    p->add(s.substr(start, end - start));
    p->invertir();
    return p;
}

/**
 * @brief Convierte una lista a un string
 *
 * @param    lista - lista
 * @return string
 */
string Calculadora::lista_a_string(Lista<string> *lista)
{
    Lista<string> *l = lista->copy();
    string s = "";
    while (!l->esvacia())
    {
        s += l->cabeza();
        l->borrar();
        if (l->esvacia())
            break;
        s += " ";
    }
    delete l;
    return s;
}

/**
 * @brief Devuelve si un string es un operador
 *
 * @param    op - string a evaluar
 * @return bool - true si es un operador
 */
bool Calculadora::es_operador(string op)
{
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "==" || op == "<=" || op == "<" || op == ">" || op == ">=" || op == "!=";
}

/**
 * @brief Verifica que un caracter sea un numero
 *
 * @param    num - Caracter a verificar
 * @return bool, true si es un numero, false c.c.
 */
bool Calculadora::es_numero(char num)
{
    return (48 <= (int)num && (int)num <= 57);
}

/**
 * @brief Verifica si un caracter es letra minuscula
 *
 * @param    minus - caracter a verificar
 * @return bool, true si es minuscula, false c.c.
 */
bool Calculadora::es_minus(char minus)
{
    return !((int)minus > 122 || (int)minus < 97);
}

/**
 * @brief Devuelve la precedencia del operador
 *
 * @param    op - operador
 * @return int
 */
int Calculadora::get_precedencia(string op)
{
    // se asigna la precedencia a cada operador segun: https://developer.mozilla.org/es/docs/Web/JavaScript/Reference/Operators/Operator_Precedence
    if (op == "*" || op == "/")
        return 5;

    if (op == "+" || op == "-")
        return 4;

    if (op == "<" || op == "<=" || op == ">" || op == ">=")
        return 8;

    if (op == "==" || op == "!=")
        return 9;
    return 0;
}

/**
 * @brief Remplaza las variables presentes en una lista por su valor correspondiente
 *
 * @param    l - lista para reemplazar las variables
 * @param    vars - lista de variables
 */
void Calculadora::reemplazar_variables(Lista<string> *l, Lista<Variable *> *vars)
{
    Lista<char> chars = *new Lista<char>(); // 'a' , 'b' , 'c' , 'd'
    Lista<char> lista_de_control = *chars.copy();
    Lista<string> copia = *l->copy(); // "a" , "b" , "c" , "d"

    // crear copia de caracteres
    while (!copia.esvacia())
    {
        chars.add(copia.last()[0]);
        copia.borrar_last();
    }

    int len = vars->size();

    // reemplazar los caracteres coincidentes
    for (int i = 0; i < len; i++)
    {
        Variable *var_i = vars->get(i); // obtengo variable i
        char n_i = var_i->getName();    // nombre de variable i

        if (chars.esta(n_i) && !var_i->is_asignada())
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "La variable " << n_i << " no fue asignada" << endl;
            exit(1);
        }

        int v_i = var_i->getValor(); // valor de variable i

        string s_i = to_string(v_i); // convierto a string el valor

        // 'a' , 'b' , 'c' , 'd'
        int pos = chars.buscar(n_i); // posicion de la variable en la lista

        l->reemplazar(pos, s_i); // reemplazo el string de la posicion pos por el valor de la variable

        lista_de_control.borrarDato(n_i); // vamos borrando las variables que ya reemplazamos
    }

    for (int i = 0; i < lista_de_control.size(); i++)
    {
        char c = lista_de_control.get(i);
        if (es_minus(c))
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Variable " << c << " no declarada" << endl;

            exit(1);
        }
    }
}

/**
 * @brief Verifica que una expresion aritmetica tenga parentesis equilibrados
 *
 * @param    cadena - string a verificar
 * @return bool, true si esta equilibrada, false c.c.
 */
bool Calculadora::es_equilibrada(string cadena)
{
    Pila<char> *p = new Pila<char>();
    int error = 0;
    for (int i = 0; (i < cadena.length() && error != 56); i++)
    {
        char c = cadena.at(i);

        switch (c)
        {
        case '(':
            p->apilar(c);
            break;
        case ')':
            if (p->tope() == '(')
            {
                p->desapilar();
                break;
            }
            error = 56;
            break;

        default:
            break;
        }
    }
    bool res = p->pilavacia();
    if (!res || error == 56)
    {
        delete p;
        return false;
    }

    delete p;

    return true;
}

#endif
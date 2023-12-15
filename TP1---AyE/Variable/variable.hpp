#pragma once
#ifndef VARIABLE_H
#define VARIABLE_H

enum TIPO
{
    BOOL,
    INT,
};
class Variable
{
private:
    int valor;
    char name;
    TIPO tipo;
    bool asignada = false;

public:
    Variable(){};
    ~Variable(){};

    Variable(char n, TIPO t)
    {
        if ((int)n > 122 || (int)n < 97)
        {
            std::cerr << "Ocurrio un error" << endl;
            std::cerr << "Invalid Variable name: " << n << endl;
            exit(1);
        }
        tipo = t;
        name = n;
    };

    void setValor(int d)
    {
        asignada = true;
        valor = d;
    };

    int getValor()
    {
        if (getTipo() == BOOL)
            return (valor && valor);

        return valor;
    };

    TIPO getTipo()
    {
        return tipo;
    };

    char getName()
    {
        return name;
    };

    bool is_asignada()
    {
        return asignada;
    };
};

#endif
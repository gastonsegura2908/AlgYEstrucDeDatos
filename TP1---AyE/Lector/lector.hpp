#pragma once
#ifndef LECTOR_H
#define LECTOR_H
#include "../Pila/pila.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Lector
{
public:
    static void leer(string path, Pila<string> *output)
    {
        fstream file;

        // open a file to perform read operation using file object
        file.open(path, ios::in);

        if (!file)
        {
            std::cerr << "\nArchivo " << path << " no encontrado" << endl;
            exit(1);
        }

        if (!file.is_open())
        {
            std::cerr << "Failed to Open File" << endl;
            exit(1);
        }

        string line;
        while (getline(file, line))
        {
            // agregar linea a la pila
            output->add(line);
        }
        file.close();
        output->invertir();
    };
};

#endif
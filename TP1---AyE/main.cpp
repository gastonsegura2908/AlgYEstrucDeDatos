#include "./Lector/lector.hpp"
#include "./Procesador/procesador.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    // validamos la entrada al programa
    if (argc != 2)
    {
        cout << "\nUso: main <file.txt>" << endl;
        return 1;
    }

    Pila<string> *instrucciones = new Pila<string>();

    // // leemos el archivo
    Lector::leer(argv[1], instrucciones);

    // Convertimos la Pila de strings a una Lista de Instrucciones
    Lista<Instruccion *> *lista = Procesador::compilar(instrucciones);

    // Procesamos la lista de Instrucciones
    Procesador::procesar(lista);

    // Liberamos memoria
    delete lista, instrucciones;

    return 0;
}
#include "./clases/Lector/lector.hpp"
#include "./clases/Arbol/arbolB.hpp"

int main(int argc, char *argv[])
{
    Lista<string> lineas = Lista<string>();

    // leemos el archivo
    Lector::leer("./pruebas.json", &lineas);

    cout << "\n -- ORDENANDO DESPUES DE CARGAR LOS DATOS" << endl;
    // ordenar despues de armar el arbol

    // crear arbol m-ario
    ArbolM arbol = ArbolM();
    arbol.CrearJson(&lineas);

    // arbol.Recorrer();
    cout << "ORDENANDO" << endl;
    arbol.Ordenar("firstname", false);
    cout << "ORDENADO" << endl;

    // representar arbol m-ario en un arbol binario
    ArbolB<string> arbolB = ArbolB<string>();
    arbolB.PasarMaB(&arbol);

    arbolB.RID();

    return 0;
}
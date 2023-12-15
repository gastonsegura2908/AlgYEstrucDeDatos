#include "./clases/Lector/lector.hpp"
#include "./clases/Arbol/arbolB.hpp"

int main(int argc, char *argv[])
{
    // validamos la entrada al programa
    if (argc < 2)
    {
        cout << "\nUso: main <file.json> <flags: -o -po <llave> <es_numero> >" << endl;
        return 1;
    }

    Lista<string> lineas = Lista<string>();

    // leemos el archivo
    Lector::leer(argv[1], &lineas);

    if (argc == 2)
    {
        // Solo Creamos los arboles y los imprimimos
        cout << "\nARBOL M-ARIO Y BINARIO SIN ORDEN" << endl;

        // crear arbol m-ario
        ArbolM arbol = ArbolM();
        arbol.CrearJson(&lineas);
        arbol.Recorrer();

        // representar arbol m-ario en un arbol binario
        ArbolB<string> arbolB = ArbolB<string>();
        arbolB.PasarMaB(&arbol);
        arbolB.RID();
    }
    else
    {
        try
        {
            string llave(argv[3]);
            string arg2(argv[2]);
            string arg4(argv[4]);

            bool es_numero = (arg4 == "true");

            if (arg2 == "-o")
            {
                cout << "\n -- ORDENANDO DESPUES DE CARGAR LOS DATOS" << endl;
                // ordenar despues de armar el arbol

                // crear arbol m-ario
                ArbolM arbol = ArbolM();
                arbol.CrearJson(&lineas);

                // arbol.Recorrer();
                cout << "ORDENANDO" << endl;
                arbol.Ordenar(llave, es_numero);
                cout << "ORDENADO" << endl;

                // representar arbol m-ario en un arbol binario
                ArbolB<string> arbolB = ArbolB<string>();
                arbolB.PasarMaB(&arbol);

                arbolB.RID();
            }
            else
            {
                cout << "\n -- ORDENANDO AL CARGAR LOS DATOS" << endl;
                // ordenar al armar el arbol

                // crear arbol m-ario
                ArbolM arbol = ArbolM();
                arbol.CrearJson(&lineas);
                arbol.Recorrer();

                // representar arbol m-ario en un arbol binario
                ArbolB<string> arbolB = ArbolB<string>();
                arbolB.PasarMaBOrdenado(&arbol, llave, es_numero);
                arbolB.RID();
            }
        }
        catch (const std::exception &e)
        {
            // error al ingresar los comandos
            cout << "Error, revise los parametros del comando" << endl;
            cerr << e.what() << '\n';
            cout << "\nUso: main <file.json> <flags: -o -po <llave> <es_numero> >" << endl;
        }
    }

    return 0;
}
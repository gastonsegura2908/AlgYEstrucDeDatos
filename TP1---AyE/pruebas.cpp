#include "./Lector/lector.hpp"
#include "./Procesador/procesador.hpp"
#include <iostream>
using namespace std;

int main()
{
    Declaracion pr = *new Declaracion("INT a");
    Instruccion *a = new Instruccion();
    Asignacion prueb1 = *new Asignacion("a = ( ( 5 ) + 1 )"); // no rechaza
    Asignacion prueb2 = *new Asignacion("a = ( b ) + 5 )");   // rechaza
    Asignacion prueb3 = *new Asignacion("a = (5 + a6");       // rechaza
    Asignacion prueb4 = *new Asignacion("a = #");             // rechaza
    Asignacion prueb5 = *new Asignacion("a = ( 5 + 2 ) * 2"); // no rechaza
    Asignacion prueb6 = *new Asignacion("a = 5 + 2 * 2");     // no rechaza
    Asignacion prueb7 = *new Asignacion("b = [ ");            // rechaza
    Asignacion prueb8 = *new Asignacion("a = [ + []");        // rechaza
    Asignacion prueb9 = *new Asignacion("a = $ + & ");        // rechaza
    Asignacion prueb10 = *new Asignacion("a = $$ + ## ");     // rechaza
    Asignacion prueb11 = *new Asignacion("a = 111 + 111");    // no rechaza
    Asignacion prueb12 = *new Asignacion("a = $$s");          // rechaza
    Asignacion prueb13 = *new Asignacion("a % ");             // rechaza
    cout << "Prueb 1: "
         << "Aritemtica: " << prueb1.getEx() << " Postfija: " << prueb1.getExPos() << " Var: " << prueb1.getName() << endl;
    cout << "Prueb 2: " << prueb2.getEx() << " " << prueb2.getExPos() << " " << prueb2.getName() << endl;
    cout << "Prueb 3: " << prueb3.getEx() << " " << prueb3.getExPos() << " " << prueb3.getName() << endl;
    cout << "Prueb 4: " << prueb4.getEx() << " " << prueb4.getExPos() << " " << prueb4.getName() << endl;
    cout << "Prueb 5: " << prueb5.getEx() << " " << prueb5.getExPos() << " " << prueb5.getName() << endl;
    cout << "Prueb 6: " << prueb6.getEx() << " " << prueb6.getExPos() << " " << prueb6.getName() << endl;
    cout << "Prueb 7: " << prueb7.getEx() << " " << prueb7.getExPos() << " " << prueb7.getName() << endl;
    cout << "Prueb 8: " << prueb8.getEx() << " " << prueb8.getExPos() << " " << prueb8.getName() << endl;
    cout << "Prueb 9: " << prueb9.getEx() << " " << prueb9.getExPos() << " " << prueb9.getName() << endl;
    cout << "Prueb 10: " << prueb10.getEx() << " " << prueb10.getExPos() << " " << prueb10.getName() << endl;
    cout << "Prueb 11: " << prueb11.getEx() << " " << prueb11.getExPos() << " " << prueb11.getName() << endl;
    cout << "Prueb 12: " << prueb12.getEx() << " " << prueb12.getExPos() << " " << prueb12.getName() << endl;
    cout << "Prueb 13: " << prueb13.getEx() << " " << prueb13.getExPos() << " " << prueb13.getName() << endl;
    return 0;
}
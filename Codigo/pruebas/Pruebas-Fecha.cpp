#include <iostream>
#include "Fecha.h"

using namespace std;

int main() {
    // PRUEBA 1: Constructor con parámetros
    // Crea una fecha específica y muestra su representación como string.
    Fecha f1(17, 5, 2025);
    Fecha f2(18, 5, 2025);

    // PRUEBA 2: Operador menor que (<)
    // Verifica si f1 es anterior a f2, debería imprimir algo.
    if (f1 < f2) {
        cout << "f1 es anterior a f2" << endl;
    }

    // PRUEBA 3: Método toString()
    // Convierte una fecha a texto y la imprime.
    char* texto = f1.toString();
    cout << "f1: " << texto << endl;
    delete[] texto;  //liberar la memoria asignada por toString()

    // PRUEBA 4: Constructor de copia y operador de igualdad (==)
    // Crea una copia exacta de f1 y verifica que sean iguales.
    Fecha f3 = f1;
    if (f1 == f3) {
        cout << "f1 y f3 son iguales" << endl;
    }

    // PRUEBA 5: Constructor por defecto
    // Verifica que al crear una fecha sin argumentos, tenga valores por defecto esperados.
    Fecha f0;
    char* s0 = f0.toString();
    cout << "f0 por defecto: " << s0 << endl;
    delete[] s0;

    // PRUEBA 6: Setters y Getters
    // Modifica una fecha usando setDia, setMes, setAnio y verifica los resultados con los getters.
    Fecha f4;
    f4.setDia(31);
    f4.setMes(12);
    f4.setAnio(1999);
    cout << "f4 (usando setters): "
         << f4.getDia() << "/"
         << f4.getMes() << "/"
         << f4.getAnio() << endl;

    // PRUEBA 7: Comparación por año
    // Compara dos fechas con mismo día y mes, pero diferente año.
    Fecha f5(10, 10, 2023);
    Fecha f6(10, 10, 2024);
    if (f5 < f6) {
        cout << "f5 es anterior a f6 (diferente anio)" << endl;
    }

    // PRUEBA 8: Comparación por día en mismo mes y año
    // Prueba si el operador < funciona con diferencia en el día.
    Fecha f7(5, 6, 2024);
    Fecha f8(10, 6, 2024);
    if (f7 < f8) {
        cout << "f7 es anterior a f8 (mismo mes y anio, diferente dia)" << endl;
    }

    return 0;
}

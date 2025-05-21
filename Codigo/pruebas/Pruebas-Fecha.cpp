#include <iostream>
#include "Fecha.h"

using namespace std;

void pruebaToString(const Fecha& f, const string& etiqueta) {
    char* texto = f.toString();
    cout << etiqueta << ": " << texto << endl;
    delete[] texto;
}

int main() {
    cout << "=== PRUEBAS CLASE Fecha ===\n\n";

    // 1. Constructor por defecto
    Fecha f0;
    cout << "[1] Por defecto:         ";
    pruebaToString(f0, "f0");

    // 2. Constructor parametrizado válido
    Fecha fv(17, 5, 2025);
    cout << "\n[2] Parametrizado valido:";
    pruebaToString(fv, "fv");
    cout << "    esValida()? " << boolalpha << fv.esValida() << "\n";

    // 3. Constructor parametrizado inválido
    Fecha fi(32, 13, -1);
    cout << "\n[3] Parametrizado invalido:";
    pruebaToString(fi, "fi");
    cout << "    esValida()? " << boolalpha << fi.esValida() << "\n";

    // 4. Constructor de copia
    Fecha fc = fv;
    cout << "\n[4] Copia de fv:         ";
    pruebaToString(fc, "fc");
    cout << "    fv == fc? " << (fv == fc) << "\n";

    // 5. Operador de asignación
    Fecha fa;
    fa = Fecha(1, 1, 2001);
    cout << "\n[5] Asignacion:          ";
    pruebaToString(fa, "fa");
    cout << "    fa.esValida()? " << fa.esValida() << "\n";

    // 6. Setters, getters y validación
    Fecha fs;
    cout << "\n[6] Setters invalidos:   ";
    fs.setDia(31); fs.setMes(2); fs.setAnio(2021);  // 31/2/2021 no existe
    pruebaToString(fs, "fs");
    cout << "    fs.esValida()? " << fs.esValida() << "\n";
    cout << "    Ajustamos a 28/2/2021\n";
    fs.setDia(28); fs.setMes(2); fs.setAnio(2021);
    pruebaToString(fs, "fs");
    cout << "    fs.esValida()? " << fs.esValida() << "\n";

    // 7. Suma de días
    Fecha fsum(25, 12, 2024);
    Fecha fnuevo = fsum + 10;  // debe pasar a 4/1/2025
    cout << "\n[7] Suma de dias:        ";
    pruebaToString(fsum, "original");
    pruebaToString(fnuevo, "original + 10 dias");

    // 8. Comparaciones de rango
    Fecha hoy(1, 1, 2025);
    Fecha inicio(25, 12, 2024);
    Fecha fin = inicio + 15;   // 9/1/2025
    cout << "\n[8] Rango de vigencia:\n";
    pruebaToString(hoy,    "hoy");
    pruebaToString(inicio, "inicio");
    pruebaToString(fin,    "fin");
    cout << "    hoy >= inicio? " << (hoy >= inicio) << "\n";
    cout << "    hoy <= fin?    " << (hoy <= fin)    << "\n";
    cout << "    vigencia?      "
         << ((hoy >= inicio && hoy <= fin) ? "SI" : "NO")
         << "\n";

    cout << "\n=== FIN DE PRUEBAS ===\n";
    return 0;
}

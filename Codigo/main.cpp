#include "UdeAStay.h"
#include <iostream>
using namespace std;

int main() {
    UdeAStay sistema;

    sistema.cargarDatosDesdeArchivos();

    cout << "\nSistema cargado exitosamente.\n" << endl;
    sistema.mostrarResumenDatos();

    int opcion;
    do {
        cout << "\n========== MENU DE PRUEBA ==========\n";
        cout << "1. Crear nueva reserva\n";
        cout << "2. Anular reserva\n";
        cout << "3. Ver reservas por anfitrion\n";
        cout << "4. Actualizar historico\n";
        cout << "5. Medir consumo de recursos\n";
        cout << "6. Guardar datos\n";
        cout << "0. Salir\n";
        cout << "====================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }
        cin.ignore();

        if (opcion == 1) {
            char docHuesped[20], codAloj[20], anotaciones[1000];
            int d, m, a, duracion, metodoPago;
            double monto;

            cout << "Documento del huesped: ";
            cin.getline(docHuesped, 20);

            cout << "Codigo del alojamiento: ";
            cin.getline(codAloj, 20);

            cout << "Fecha entrada (dd mm aaaa): ";
            cin >> d >> m >> a;
            if (cin.fail()) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Fecha invalida.\n"; continue;
            }
            Fecha entrada(d, m, a);

            cout << "Duracion (noches): ";
            cin >> duracion;
            if (cin.fail()) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Duracion invalida.\n"; continue;
            }

            cout << "Metodo de pago (0 = PSE, 1 = TCredito): ";
            cin >> metodoPago;
            if (cin.fail() || (metodoPago != 0 && metodoPago != 1)) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Metodo de pago invalido.\n"; continue;
            }
            cin.ignore();

            cout << "Fecha pago (dd mm aaaa): ";
            cin >> d >> m >> a;
            if (cin.fail()) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Fecha de pago invalida.\n"; continue;
            }
            Fecha pago(d, m, a);

            cout << "Monto total: ";
            cin >> monto;
            if (cin.fail()) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Monto invalido.\n"; continue;
            }
            cin.ignore();

            cout << "Anotaciones: ";
            cin.getline(anotaciones, 1000);

            sistema.crearReserva(docHuesped, codAloj, entrada, duracion, metodoPago, pago, monto, anotaciones);

        } else if (opcion == 2) {
            char codigo[20];
            cout << "Codigo de la reserva a anular: ";
            cin.getline(codigo, 20);
            sistema.anularReserva(codigo);

        } else if (opcion == 3) {
            char doc[20];
            int d1, m1, a1, d2, m2, a2;
            cout << "Documento del anfitrion: ";
            cin.getline(doc, 20);

            cout << "Fecha desde (dd mm aaaa): ";
            cin >> d1 >> m1 >> a1;
            if (cin.fail()) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Fecha invalida.\n"; continue;
            }

            cout << "Fecha hasta (dd mm aaaa): ";
            cin >> d2 >> m2 >> a2;
            if (cin.fail()) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Fecha invalida.\n"; continue;
            }
            cin.ignore();

            sistema.consultarReservasAnfitrion(doc, Fecha(d1, m1, a1), Fecha(d2, m2, a2));

        } else if (opcion == 4) {
            int d, m, a;
            cout << "Nueva fecha de corte (dd mm aaaa): ";
            cin >> d >> m >> a;
            if (cin.fail()) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Entrada invalida. Debes ingresar una fecha con formato: dd mm aaaa\n";
                continue;
            }
            cin.ignore();
            sistema.actualizarHistorico(Fecha(d, m, a));
            cout << "Historico actualizado.\n";

        } else if (opcion == 5) {
            sistema.medirConsumoDeRecursos();

        } else if (opcion == 6) {
            sistema.guardarDatosEnArchivos();
            cout << "Datos guardados correctamente.\n";

        } else if (opcion != 0) {
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    cout << "\nFinalizando programa...\n";
    return 0;
}

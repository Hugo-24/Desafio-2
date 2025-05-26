#include "UdeAStay.h"
#include <iostream>

using namespace std;

int main() {
    UdeAStay sistema;
    sistema.cargarDatosDesdeArchivos();
    sistema.mostrarResumenDatos();

    cout << "\n===== INICIO DE SESION =====\n";
    cout << "Seleccione su rol:\n";
    cout << "0. Anfitrion\n";
    cout << "1. Huesped\n";
    cout << "Ingrese opcion: ";
    int tipoUsuario;
    cin >> tipoUsuario;
    cin.ignore();

    if (tipoUsuario != 0 && tipoUsuario != 1) {
        cout << "Rol invalido. Terminando programa.\n";
        return 1;
    }

    char documento[20];
    cout << "Ingrese su documento de identidad: ";
    cin.getline(documento, 20);

    if (!sistema.iniciarSesion(documento, tipoUsuario)) {
        cout << "No se encontro el usuario. Terminando programa.\n";
        return 1;
    }

    int opcion;
    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        if (tipoUsuario == 0) {
            cout << "1. Consultar reservas en rango\n";
            cout << "2. Anular reserva\n";
        } else {
            cout << "1. Crear nueva reserva\n";
            cout << "2. Anular reserva\n";
        }
        cout << "0. Cerrar sesion\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            if (tipoUsuario == 0) {
                // Consultar reservas por anfitrión
                int d1, m1, a1, d2, m2, a2;
                cout << "Fecha desde (dd mm aaaa): ";
                cin >> d1 >> m1 >> a1;
                cout << "Fecha hasta (dd mm aaaa): ";
                cin >> d2 >> m2 >> a2;
                cin.ignore();
                sistema.consultarReservasAnfitrion(documento, Fecha(d1, m1, a1), Fecha(d2, m2, a2));
            } else {
                // Crear nueva reserva
                char codAloj[20], anotaciones[1000];
                int d, m, a, duracion, metodoPago;
                double monto;

                cout << "Codigo del alojamiento: ";
                cin.getline(codAloj, 20);

                cout << "Fecha entrada (dd mm aaaa): ";
                cin >> d >> m >> a;
                Fecha entrada(d, m, a);

                cout << "Duracion (noches): ";
                cin >> duracion;

                cout << "Metodo de pago (0 = PSE, 1 = TCredito): ";
                cin >> metodoPago;

                cout << "Fecha pago (dd mm aaaa): ";
                cin >> d >> m >> a;
                Fecha pago(d, m, a);

                cout << "Monto total: ";
                cin >> monto;
                cin.ignore();

                cout << "Anotaciones: ";
                cin.getline(anotaciones, 1000);

                sistema.crearReserva(documento, codAloj, entrada, duracion, metodoPago, pago, monto, anotaciones);
            }
        } else if (opcion == 2) {
            char codigo[20];
            cout << "Codigo de la reserva a anular: ";
            cin.getline(codigo, 20);
            sistema.anularReserva(codigo);
        } else if (opcion != 0) {
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    sistema.cerrarSesion();
    sistema.guardarDatosEnArchivos();
    cout << "\nSesion cerrada y datos guardados correctamente.\n";
    sistema.medirConsumoDeRecursos();

    return 0;
}

#include "UdeAStay.h"
#include <iostream>
#include "Funciones.h"

// Constantes para distinguir tipos de usuario
#define TIPO_HUESPED 1
#define TIPO_ANFITRION 2

using namespace std;

int main() {
    UdeAStay sistema;

    // Carga inicial de datos desde archivos (no aparece en el menu)
    sistema.cargarDatosDesdeArchivos();

    int opcionPrincipal;

    do {
        // Menu principal del sistema
        cout << "\n===== BIENVENIDO A UdeAStay =====\n";
        cout << "1) Iniciar sesion como HUESPED\n";
        cout << "2) Iniciar sesion como ANFITRION\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        cin >> opcionPrincipal;

        // Validacion de entrada
        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Entrada invalida.\n";
            continue;
        }

        // --- MENU HUESPED ---
        if (opcionPrincipal == TIPO_HUESPED) {
            char documento[50];
            cout << "Documento de identidad: ";
            cin >> documento;

            if (sistema.iniciarSesion(documento, TIPO_HUESPED)) {
                int opcionH;
                do {
                    Huesped* h = sistema.getHuespedActivo();
                    cout << "\n==== MENU HUESPED: " << h->getNombreCompleto() << " ====\n";
                    cout << "1) Reservar alojamiento\n";
                    cout << "2) Anular reservacion\n";
                    cout << "3) Ver mis reservas\n";
                    cout << "0) Cerrar sesion\n";
                    cout << "Opcion: ";
                    cin >> opcionH;

                    if (cin.fail()) {
                        cin.clear(); cin.ignore(1000, '\n');
                        cout << "Entrada invalida.\n";
                        continue;
                    }

                    if (opcionH == 1) {
                        int d, m, a, noches;
                        char municipio[100];
                        double precioMax;
                        float puntuacionMin;

                        char bufferFecha[20];
                        cout << "Fecha entrada (dd mm aaaa): ";
                        cin.ignore();  // limpia el buffer anterior por si acaso
                        cin.getline(bufferFecha, 20);
                        extraerFecha(bufferFecha, d, m, a);
                        if (d == 0 || m == 0 || a == 0) {
                            cout << "Formato de fecha invalido. Use espacios, guiones o barras.\n";
                            continue;
                        }
                        Fecha fechaEntrada(d, m, a);

                        if (!fechaEntrada.esValida()) {
                            cout << "Fecha invalida. Intente de nuevo.\n";
                            continue;
                        }
                        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Fecha invalida.\n"; continue; }

                        cout << "Duracion (noches): ";
                        cin >> noches;
                        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Duracion invalida.\n"; continue; }

                        cout << "Municipio: ";
                        cin >> municipio;

                        cout << "Precio maximo por noche (-1 para omitir): ";
                        cin >> precioMax;
                        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Precio invalido.\n"; continue; }

                        cout << "Puntuacion minima del anfitrion (0-5, -1 para omitir): ";
                        cin >> puntuacionMin;
                        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Puntuacion invalida.\n"; continue; }
                        sistema.buscarAlojamientos(Fecha(d, m, a), noches, municipio, precioMax, puntuacionMin, 0);
                        cout << "--- Metricas UdeAStay ---\n";
                        sistema.medirConsumoDeRecursos();

                    } else if (opcionH == 2) {
                        char codigo[20];
                        cout << "Codigo de reserva a anular: ";
                        cin >> codigo;
                        sistema.anularReserva(codigo);
                        cout << "--- Metricas UdeAStay ---\n";
                        sistema.medirConsumoDeRecursos();

                    } else if (opcionH == 3) {
                        sistema.mostrarReservasHuespedActivo();
                        cout << "--- Metricas UdeAStay ---\n";
                        sistema.medirConsumoDeRecursos();

                    } else if (opcionH == 0) {
                        sistema.cerrarSesion();
                        sistema.guardarDatosEnArchivos();
                    } else {
                        cout << "Opcion invalida.\n";
                    }

                } while (opcionH != 0);
            }

            // --- MENU ANFITRION ---
        } else if (opcionPrincipal == TIPO_ANFITRION) {
            char documento[50];
            cout << "Documento de identidad: ";
            cin >> documento;

            if (sistema.iniciarSesion(documento, TIPO_ANFITRION)) {
                int opcionA;
                do {
                    Anfitrion* a = sistema.getAnfitrionActivo();
                    cout << "\n==== MENU ANFITRION: " << a->getNombreCompleto() << " ====\n";
                    cout << "1) Consultar mis reservas (rango de fechas)\n";
                    cout << "2) Anular reservacion\n";
                    cout << "3) Actualizar historico\n";
                    cout << "0) Cerrar sesion\n";
                    cout << "Opcion: ";
                    cin >> opcionA;

                    if (cin.fail()) {
                        cin.clear(); cin.ignore(1000, '\n');
                        cout << "Entrada invalida.\n";
                        continue;
                    }

                    if (opcionA == 1) {
                        int d1, m1, a1, d2, m2, a2;
                        cout << "Fecha inicio (dd mm aaaa): ";
                        cin >> d1 >> m1 >> a1;
                        cout << "Fecha fin (dd mm aaaa): ";
                        cin >> d2 >> m2 >> a2;
                        if (cin.fail()) {
                            cin.clear(); cin.ignore(1000, '\n');
                            cout << "Fechas invalidas.\n"; continue;
                        }

                        sistema.consultarReservasAnfitrion(documento, Fecha(d1, m1, a1), Fecha(d2, m2, a2));
                        cout << "--- Metricas UdeAStay ---\n";
                        sistema.medirConsumoDeRecursos();

                    } else if (opcionA == 2) {
                        char codigo[20];
                        cout << "Codigo de reserva a anular: ";
                        cin >> codigo;
                        sistema.anularReserva(codigo);
                        cout << "--- Metricas UdeAStay ---\n";
                        sistema.medirConsumoDeRecursos();

                    } else if (opcionA == 3) {
                        int d, m, a;
                        cout << "Nueva fecha de corte (dd mm aaaa): ";
                        cin >> d >> m >> a;
                        if (cin.fail()) {
                            cin.clear(); cin.ignore(1000, '\n');
                            cout << "Fecha invalida.\n"; continue;
                        }

                        sistema.actualizarHistorico(Fecha(d, m, a));
                        cout << "--- Metricas UdeAStay ---\n";
                        sistema.medirConsumoDeRecursos();

                    } else if (opcionA == 0) {
                        sistema.cerrarSesion();
                        sistema.guardarDatosEnArchivos();
                    } else {
                        cout << "Opcion invalida.\n";
                    }

                } while (opcionA != 0);
            }

            // --- SALIR ---
        } else if (opcionPrincipal == 0) {
            sistema.guardarDatosEnArchivos();
            cout << "Gracias por usar UdeAStay. Hasta pronto!\n";

        } else {
            cout << "Opcion invalida.\n";
        }

    } while (opcionPrincipal != 0);

    return 0;
}

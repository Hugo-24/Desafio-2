#include "UdeAStay.h"
#include <iostream>
#define TIPO_HUESPED 1
#define TIPO_ANFITRION 0

using namespace std;

int main() {
    UdeAStay sistema;
    // Cargar datos al iniciar el programa (sin mostrar en el menu)
    sistema.cargarDatosDesdeArchivos();

    int opcionPrincipal;
    do {
        // Menu principal
        cout << "==== UdeAStay ====" << endl;
        cout << "1) Iniciar sesionn como HUESPED" << endl;
        cout << "2) Iniciar sesionn como ANFITRION" << endl;
        cout << "0) Salir" << endl;
        cout << "Opcion: ";
        cin >> opcionPrincipal;

        if (opcionPrincipal == 1) {
            // Inicio de sesion de Huesped
            char documento[50];
            cout << "Documento de identidad: ";
            cin >> documento;
            // Intentar iniciar sesion como huesped
            if (sistema.iniciarSesion(documento, TIPO_HUESPED)) {
                // Obtener puntero al huesped activo para mostrar nombre
                Huesped* huespedActivo = sistema.getHuespedActivo();
                const char* nombreH = (huespedActivo != nullptr) ? huespedActivo->getNombreCompleto() : "";
                int opcionHuesped;
                do {
                    // Menu de huesped
                    cout << "==== MENU DE HUESPED: " << nombreH << " ====" << endl;
                    cout << "1) Reservar alojamiento" << endl;
                    cout << "2) Anular reservacion" << endl;
                    cout << "3) Ver mis reservas" << endl;
                    cout << "0) Cerrar sesion" << endl;
                    cout << "Opcion: ";
                    cin >> opcionHuesped;

                    if (opcionHuesped == 1) {
                        // Reservar alojamiento
                        int d1, m1, a1;
                        cout << "Fecha de entrada (dd mm aaaa): ";
                        cin >> d1 >> m1 >> a1;
                        int duracion;
                        cout << "Duracion (noches): ";
                        cin >> duracion;
                        char municipio[100];
                        cout << "Municipio: ";
                        cin >> municipio;
                        double precioMax;
                        cout << "Precio maximo (o -1 para omitir): ";
                        cin >> precioMax;
                        float puntuacionMin;
                        cout << "Puntuacion minima (0-5, o -1 para omitir): ";
                        cin >> puntuacionMin;
                        // Llamada a la busqueda de alojamientos y creacion de reserva
                        Fecha fechaEntrada(d1, m1, a1);
                        sistema.buscarAlojamientos(fechaEntrada, duracion, municipio, precioMax, puntuacionMin, 0);

                        // Mostrar metricas del sistema
                        cout << "--- Metricas UdeAStay ---" << endl;
                        sistema.medirConsumoDeRecursos();
                    }
                    else if (opcionHuesped == 2) {
                        // Anular reservacion
                        char codigoReserva[20];
                        cout << "Codigo de reserva a anular: ";
                        cin >> codigoReserva;
                        sistema.anularReserva(codigoReserva);

                        // Mostrar metricas del sistema
                        cout << "--- Metricas UdeAStay ---" << endl;
                        sistema.medirConsumoDeRecursos();
                    }
                    else if (opcionHuesped == 3) {
                        // Ver mis reservas
                        // (No existe una funcion implementada para esto en el sistema)
                        cout << "Mis reservas (actualmente no implementado para lista específica)." << endl;

                        // Mostrar metricas del sistema
                        cout << "--- Metricas UdeAStay ---" << endl;
                        sistema.medirConsumoDeRecursos();
                    }
                    else if (opcionHuesped == 0) {
                        // Cerrar sesion de huesped y guardar datos
                        sistema.cerrarSesion();
                        sistema.guardarDatosEnArchivos();
                    }
                    else {
                        cout << "Opcion invalida. Intente de nuevo." << endl;
                    }
                } while (opcionHuesped != 0);
            }
            // Si falla el inicio de sesion, volver al menu principal
        }
        else if (opcionPrincipal == 2) {
            // Inicio de sesion de Anfitrion
            char documento[50];
            cout << "Documento de identidad: ";
            cin >> documento;
            // Intentar iniciar sesion como anfitrion
            if (sistema.iniciarSesion(documento, TIPO_ANFITRION)) {
                // Obtener puntero al anfitrion activo para mostrar nombre
                Anfitrion* anfitrionActivo = sistema.getAnfitrionActivo();

                const char* nombreA = (anfitrionActivo != nullptr) ? anfitrionActivo->getNombreCompleto() : "";
                int opcionAnfitrion;
                do {
                    // Menu de anfitrion
                    cout << "==== MENU DE ANFITRION: " << nombreA << " ====" << endl;
                    cout << "1) Consultar mis reservas (rango de fechas)" << endl;
                    cout << "2) Anular reservacion" << endl;
                    cout << "3) Actualizar historico" << endl;
                    cout << "0) Cerrar sesion" << endl;
                    cout << "Opcion: ";
                    cin >> opcionAnfitrion;

                    if (opcionAnfitrion == 1) {
                        // Consultar reservas del anfitrion en un rango de fechas
                        int d1, m1, a1, d2, m2, a2;
                        cout << "Fecha inicio (dd mm aaaa): ";
                        cin >> d1 >> m1 >> a1;
                        cout << "Fecha fin (dd mm aaaa): ";
                        cin >> d2 >> m2 >> a2;
                        Fecha inicio(d1, m1, a1);
                        Fecha fin(d2, m2, a2);
                        sistema.consultarReservasAnfitrion(documento, inicio, fin);

                        // Mostrar metricas del sistema
                        cout << "--- Metricas UdeAStay ---" << endl;
                        sistema.medirConsumoDeRecursos();
                    }
                    else if (opcionAnfitrion == 2) {
                        // Anular reservaci\u00F3n (igual que en huesped)
                        char codigoReserva[20];
                        cout << "Codigo de reserva a anular: ";
                        cin >> codigoReserva;
                        sistema.anularReserva(codigoReserva);

                        // Mostrar metricas del sistema
                        cout << "--- Metricas UdeAStay ---" << endl;
                        sistema.medirConsumoDeRecursos();
                    }
                    else if (opcionAnfitrion == 3) {
                        // Actualizar historico moviendo reservas antiguas
                        int d1, m1, a1;
                        cout << "Nueva fecha de corte (dd mm aaaa): ";
                        cin >> d1 >> m1 >> a1;
                        Fecha nuevaFecha(d1, m1, a1);
                        sistema.actualizarHistorico(nuevaFecha);

                        // Mostrar metricas del sistema
                        cout << "--- M\etricas UdeAStay ---" << endl;
                        sistema.medirConsumoDeRecursos();
                    }
                    else if (opcionAnfitrion == 0) {
                        // Cerrar sesion de anfitrion y guardar datos
                        sistema.cerrarSesion();
                        sistema.guardarDatosEnArchivos();
                    }
                    else {
                        cout << "Opcion invalida. Intente de nuevo." << endl;
                    }
                } while (opcionAnfitrion != 0);
            }
            // Si falla el inicio de sesion, volver al menu principal
        }
        else if (opcionPrincipal == 0) {
            // Salir del sistema
            sistema.guardarDatosEnArchivos();
        }
        else {
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcionPrincipal != 0);

    return 0;
}

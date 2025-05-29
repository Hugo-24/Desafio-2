#include "UdeAStay.h"      // Archivo que contiene la lógica principal del sistema
#include "Funciones.h"     // Funciones auxiliares para trabajar con fechas, texto, etc.
#include <iostream>

#define TIPO_HUESPED 1
#define TIPO_ANFITRION 2

using namespace std;

// Declaramos funciones que vamos a usar para organizar mejor el código
void mostrarMetricas(UdeAStay& sistema);
void menuHuesped(UdeAStay& sistema);
void menuAnfitrion(UdeAStay& sistema);

int main() {
    // Creamos el sistema de reservas UdeAStay
    UdeAStay sistema;

    // Cargamos todos los datos desde los archivos .txt
    // Esto no lo ve el usuario, pero es lo que permite que todo funcione con la info guardada
    sistema.cargarDatosDesdeArchivos();
    int opcionPrincipal;

    // Menú principal para escoger si entra como huésped o anfitrión
    do {
        cout << "\n===== BIENVENIDO A UdeAStay =====\n";
        cout << "1) Iniciar sesion como HUESPED\n";
        cout << "2) Iniciar sesion como ANFITRION\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        cin >> opcionPrincipal;

        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Entrada invalida.\n"; continue; }

        if (opcionPrincipal == TIPO_HUESPED) {
            menuHuesped(sistema);
        } else if (opcionPrincipal == TIPO_ANFITRION) {
            menuAnfitrion(sistema);
        } else if (opcionPrincipal == 0) {
            // Antes de salir, guardamos todos los datos para que no se pierda nada
            sistema.guardarDatosEnArchivos();
            cout << "Gracias por usar UdeAStay. Hasta pronto!\n";
        } else {
            cout << "Opcion invalida.\n";
        }

    } while (opcionPrincipal != 0);

    return 0;
}

// Esta función simplemente muestra en pantalla cuántos recursos (memoria, ciclos) se usaron.
// Es algo que nos piden medir por temas de eficiencia.
void mostrarMetricas(UdeAStay& sistema) {
    cout << "--- Metricas UdeAStay ---\n";
    sistema.medirConsumoDeRecursos();
}

// Menú que aparece cuando entra un huésped
void menuHuesped(UdeAStay& sistema) {
    char documento[50];
    cout << "Documento de identidad: ";
    cin >> documento;

    if (!sistema.iniciarSesion(documento, TIPO_HUESPED)) return;

    int opcion;
    do {
        Huesped* h = sistema.getHuespedActivo();
        cout << "\n==== MENU HUESPED: " << h->getNombreCompleto() << " ====\n";
        cout << "1) Reservar alojamiento\n";
        cout << "2) Anular reservacion\n";
        cout << "3) Ver mis reservas\n";
        cout << "0) Cerrar sesion\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Entrada invalida.\n"; continue; }

        if (opcion == 1) {
            // --- Aquí el huésped quiere hacer una reserva ---
            int d, m, a, noches;
            char municipio[100];
            double precioMax;
            float puntuacionMin;
            char bufferFecha[20];

            // Usamos un buffer para leer la fecha completa como texto (por si mete guiones o espacios)
            // Le damos tamaño 20 para que pueda escribir algo tipo "20-12-2025" con tranquilidad
            cout << "Fecha entrada (dd mm aaaa): ";
            cin.ignore(); // limpiamos lo que queda del buffer anterior (por seguridad)
            cin.getline(bufferFecha, 20);
            extraerFecha(bufferFecha, d, m, a); // extrae los números de la fecha escrita

            Fecha fechaEntrada(d, m, a);
            if (!fechaEntrada.esValida()) { cout << "Fecha invalida.\n"; continue; }

            cout << "Duracion (noches): ";
            cin >> noches;
            if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Duracion invalida.\n"; continue; }

            cout << "Municipio: ";
            cin >> municipio;

            cout << "Precio maximo por noche (-1 para omitir): ";
            cin >> precioMax;

            cout << "Puntuacion minima del anfitrion (0-5, -1 para omitir): ";
            cin >> puntuacionMin;

            // Esta función busca alojamientos según los filtros y deja que el usuario elija uno
            sistema.buscarAlojamientos(fechaEntrada, noches, municipio, precioMax, puntuacionMin, 0);

            // Siempre mostramos cuántos recursos se usaron (como lo pide el reto)
            mostrarMetricas(sistema);

        } else if (opcion == 2) {
            // El huésped quiere anular una reserva
            char codigo[20];
            cout << "Codigo de reserva a anular: ";
            cin >> codigo;
            sistema.anularReserva(codigo);
            mostrarMetricas(sistema);

        } else if (opcion == 3) {
            // Muestra todas las reservas que tiene el huésped activo
            sistema.mostrarReservasHuespedActivo();
            mostrarMetricas(sistema);

        } else if (opcion == 0) {
            // Guardamos los datos y cerramos sesión
            sistema.cerrarSesion();
            sistema.guardarDatosEnArchivos();
        } else {
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);
}

// Menú que aparece si entra un anfitrión
void menuAnfitrion(UdeAStay& sistema) {
    char documento[50];
    cout << "Documento de identidad: ";
    cin >> documento;

    if (!sistema.iniciarSesion(documento, TIPO_ANFITRION)) return;

    int opcion;
    do {
        Anfitrion* a = sistema.getAnfitrionActivo();
        cout << "\n==== MENU ANFITRION: " << a->getNombreCompleto() << " ====\n";
        cout << "1) Consultar mis reservas (rango de fechas)\n";
        cout << "2) Anular reservacion\n";
        cout << "3) Actualizar historico\n";
        cout << "0) Cerrar sesion\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Entrada invalida.\n"; continue; }

        if (opcion == 1) {
            // Consultar reservas por fechas
            int d1, m1, a1, d2, m2, a2;
            cout << "Fecha inicio (dd mm aaaa): ";
            cin >> d1 >> m1 >> a1;
            cout << "Fecha fin (dd mm aaaa): ";
            cin >> d2 >> m2 >> a2;

            sistema.consultarReservasAnfitrion(documento, Fecha(d1, m1, a1), Fecha(d2, m2, a2));
            mostrarMetricas(sistema);

        } else if (opcion == 2) {
            // Anular una reserva como anfitrión
            char codigo[20];
            cout << "Codigo de reserva a anular: ";
            cin >> codigo;
            sistema.anularReserva(codigo);
            mostrarMetricas(sistema);

        } else if (opcion == 3) {
            // Actualizar el histórico: mueve reservas pasadas a archivo histórico
            int d, m, a;
            cout << "Nueva fecha de corte (dd mm aaaa): ";
            cin >> d >> m >> a;

            sistema.actualizarHistorico(Fecha(d, m, a));
            mostrarMetricas(sistema);

        } else if (opcion == 0) {
            sistema.cerrarSesion();
            sistema.guardarDatosEnArchivos();
        } else {
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);
}

#include <iostream>
#include "Anfitrion.h"
#include "Alojamiento.h"
#include "Reserva.h"
#include "Huesped.h"
#include "Fecha.h"

using namespace std;

int main() {
    // Crear anfitrion y alojamiento
    Anfitrion* anfitrion1 = new Anfitrion("Laura Torres", 18);
    Alojamiento* alojamiento1 = new Alojamiento("ALO001", "Casa Prueba", "Antioquia", "Medellin", "Calle 123", 0, 100000, anfitrion1);
    anfitrion1->agregarAlojamiento(alojamiento1);

    // Crear huesped
    Huesped* huesped1 = new Huesped("Carlos Ruiz", "987654321", 10);

    // Crear primera reserva (sin conflicto)
    Fecha entrada1(1, 6, 2025);
    Fecha pago1(30, 5, 2025);
    Reserva* reserva1 = new Reserva(entrada1, 2, alojamiento1, huesped1, "TCredito", pago1, 200000, "Llega en la manana");

    huesped1->agregarReserva(reserva1);
    alojamiento1->agregarReservacion(entrada1, 2);

    // Mostrar comprobante
    cout << "\nComprobante de reserva:\n";
    reserva1->mostrarComprobante();

    // Crear segunda reserva con conflicto de fechas (debe ser rechazada)
    Fecha entrada2(2, 6, 2025); // Se solapa con la anterior
    Reserva* reserva2 = new Reserva(entrada2, 3, alojamiento1, huesped1, "PSE", pago1, 300000, "Solicitud especial");

    cout << "\nIntentando agregar reserva conflictiva...\n";
    huesped1->agregarReserva(reserva2); // No se agregara

    // Mostrar cantidad de reservas reales
    cout << "\nReservas aceptadas para el huesped: " << huesped1->getCantidadReservas() << endl;

    // Mostrar resumen de huesped
    cout << "\nResumen del huesped:\n";
    huesped1->imprimirResumen();

    // Mostrar todas las reservas actuales
    cout << "\nReservas actuales:\n";
    huesped1->mostrarReservas();

    // Anular reserva
    const char* codigoAEliminar = reserva1->getCodigo();
    huesped1->anularReservacion(codigoAEliminar);

    cout << "\nReserva anulada. Reservas restantes:\n";
    huesped1->mostrarReservas();

    // Mostrar contadores
    cout << "\n--- Estadisticas ---\n";
    cout << "Huespedes creados: " << Huesped::getTotalHuespedesCreados() << endl;
    cout << "Reservas creadas: " << Reserva::getTotalReservasCreadas() << endl;
    cout << "Iteraciones en Huesped: " << Huesped::getTotalIteraciones() << endl;
    cout << "Iteraciones en Reserva: " << Reserva::getTotalIteraciones() << endl;

    // Liberar memoria
    delete reserva2;
    delete huesped1;
    delete alojamiento1;
    delete anfitrion1;

    return 0;
}

#include <iostream>
#include "Fecha.h"
#include "Anfitrion.h"
#include "Alojamiento.h"
#include "Huesped.h"
#include "Reserva.h"

int main() {
    // Crear el mismo nombre que la clase para la instancia
    Huesped Huesped("Maria Garcia", "55443322", 6, 4.0);
    std::cout << "\n=== Estado inicial ===\n";
    Huesped.imprimirResumen();   // 0 reservas

    // Preparar anfitrion y alojamiento de apoyo
    Anfitrion host("80011223", "Luis Ramirez", 18);
    Alojamiento apt("B200", "Apartamento Centro", "Antioquia", "Medellin",
                    "Cll 50 #30-10", 1, 180000.0, &host);

    // Reserva valida 1
    Fecha fe1(5, 7, 2025), pago1(1, 7, 2025);
    Reserva* r1 = new Reserva(fe1, 4, &apt, &Huesped, "PSE", pago1, 720000.0, "Sin mascotas");
    Huesped.agregarReserva(r1);

    // Reserva valida 2
    Fecha fe2(15, 7, 2025), pago2(10, 7, 2025);
    Reserva* r2 = new Reserva(fe2, 3, &apt, &Huesped, "Tarjeta de credito", pago2, 540000.0, nullptr);
    Huesped.agregarReserva(r2);

    std::cout << "\n=== Tras dos reservas validas ===\n";
    Huesped.imprimirResumen();   // 2 reservas
    Huesped.mostrarReservas();   // comprobantes

    // Intento de reserva solapada (5-9 julio)
    Fecha fe3(7, 7, 2025);
    Reserva* r3 = new Reserva(fe3, 2, &apt, &Huesped, "PSE", pago1, 360000.0, "Prueba solap");
    std::cout << "\n=== Intento solapado (debe fallar) ===\n";
    Huesped.agregarReserva(r3);
    delete r3;

    // Anular primera reserva
    std::cout << "\n=== Anulando r1 ===\n";
    Huesped.anularReservacion(r1->getCodigo());

    std::cout << "\n=== Tras anular r1 ===\n";
    Huesped.imprimirResumen();   // 1 reserva
    Huesped.mostrarReservas();   // solo r2

    // Limpiar ultima reserva
    Huesped.anularReservacion(r2->getCodigo());

    std::cout << "\n=== Estado final ===\n";
    Huesped.imprimirResumen();   // 0 reservas

    return 0;
}

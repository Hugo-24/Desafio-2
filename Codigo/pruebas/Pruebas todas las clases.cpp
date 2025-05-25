#include <iostream>
#include "Fecha.h"
#include "Anfitrion.h"
#include "Alojamiento.h"
#include "Huesped.h"
#include "Reserva.h"

using namespace std;

int main() {
    // ========== PRUEBAS DEL SISTEMA UdeAStay ==========

    // 1. Crear anfitrion
    Anfitrion* anfitrion1 = new Anfitrion("Laura Torres", 36);
    cout << "\n[Prueba 1] Anfitrion creado: " << anfitrion1->getNombreCompleto() << endl;
    cout << "Codigo generado: " << anfitrion1->getDocumentoIdentidad() << endl;

    // 2. Crear alojamiento asociado
    Alojamiento* casa1 = new Alojamiento("ALO001", "Casa Azul", "Antioquia", "Medellin", "Calle 45 #12-30", 0, 250000, anfitrion1);
    anfitrion1->agregarAlojamiento(casa1);
    cout << "\n[Prueba 2] Alojamiento creado: " << casa1->getNombre() << ", Municipio: " << casa1->getMunicipio() << endl;

    // 3. Verificar y modificar amenidades
    casa1->agregarAmenidad(0); // Wifi
    casa1->agregarAmenidad(2); // Parqueadero
    cout << "\n[Prueba 3] Amenidades iniciales:\n";
    casa1->mostrarAmenidades();
    casa1->quitarAmenidad(0);
    cout << "\nAmenidades despues de quitar Wifi:\n";
    casa1->mostrarAmenidades();

    // 4. Crear huesped
    Huesped* huesped1 = new Huesped("Carlos Martinez", "1098765432", 18);
    cout << "\n[Prueba 4] Huesped creado: " << huesped1->getNombreCompleto() << ", Documento: " << huesped1->getDocumentoIdentidad() << endl;

    // 5. Ver disponibilidad y crear reserva
    Fecha fechaReserva1(10, 6, 2025);
    cout << "\n[Prueba 5] Verificar disponibilidad en 10/06/2025: " 
         << (casa1->estaDisponible(fechaReserva1) ? "Si" : "No") << endl;

    casa1->agregarReservacion(fechaReserva1, 3); // simulado en alojamiento
    Reserva* reserva1 = new Reserva(fechaReserva1, 3, casa1, huesped1, "PSE", Fecha(1, 6, 2025), 750000, "Reserva para vacaciones");
    huesped1->agregarReserva(reserva1);

    cout << "[OK] Reserva agregada desde huesped.\n";

    // 6. Comprobante de reserva
    cout << "\n[Prueba 6] Comprobante generado:\n";
    reserva1->mostrarComprobante();

    // 7. Intentar agregar una reserva conflictiva
    cout << "\n[Prueba 7] Intentando reserva con conflicto de fechas...\n";
    Reserva* reserva2 = new Reserva(Fecha(12, 6, 2025), 2, casa1, huesped1, "TCredito", Fecha(3, 6, 2025), 500000, "Intento duplicado");
    huesped1->agregarReserva(reserva2); // No debe agregarse

    cout << "Reservas actuales del huesped: " << huesped1->getCantidadReservas() << endl;

    // 8. Anular reserva
    cout << "\n[Prueba 8] Anulando reserva RSV-0001...\n";
    huesped1->anularReservacion("RSV-0001");

    cout << "Reservas restantes: " << huesped1->getCantidadReservas() << endl;

    // 9. Ver reservas del anfitrion en un rango
    cout << "\n[Prueba 9] Consultando reservas desde el anfitrion (rango 1/6 al 30/6):\n";
    anfitrion1->verReservaciones(Fecha(1, 6, 2025), Fecha(30, 6, 2025));

    // 10. Contadores globales
    cout << "\n[Prueba 10] Estadisticas globales:\n";
    cout << "Anfitriones creados: " << Anfitrion::getTotalAnfitrionesCreados() << endl;
    cout << "Alojamientos creados: " << Alojamiento::getTotalAlojamientosCreados() << endl;
    cout << "Huespedes creados: " << Huesped::getTotalHuespedesCreados() << endl;
    cout << "Reservas creadas: " << Reserva::getTotalReservasCreadas() << endl;
    cout << "Iteraciones en Alojamiento: " << Alojamiento::getTotalIteraciones() << endl;
    cout << "Iteraciones en Huesped: " << Huesped::getTotalIteraciones() << endl;
    cout << "Iteraciones en Reserva: " << Reserva::getTotalIteraciones() << endl;

    // 11. Eliminar memoria
    delete reserva2;
    delete huesped1;
    delete casa1;
    delete anfitrion1;

    return 0;
}
#include <iostream>
#include "Alojamiento.h"
#include "Anfitrion.h"

using namespace std;

int main() {
    // Crear anfitrion de prueba
    Anfitrion* anfitrion = new Anfitrion("98765432", "Laura Torres", 24);

    // Prueba 1: Crear alojamiento
    Alojamiento* casa = new Alojamiento("ALO1", "Casa Verde", "Antioquia", "Guatape", "Cra 8 #15-23", 0, 200000, anfitrion);
    cout << "Alojamiento creado: " << casa->getNombre() << " en " << casa->getMunicipio() << endl;

    // Prueba 2: Agregar amenidades
    casa->agregarAmenidad(0); // Wifi
    casa->agregarAmenidad(2); // Parqueadero
    casa->mostrarAmenidades();

    // Prueba 3: Quitar una amenidad
    casa->quitarAmenidad(0); // Quitamos Wifi
    cout << "\nDespues de quitar Wifi:\n";
    casa->mostrarAmenidades();

    // Prueba 4: Verificar disponibilidad antes de reservar
    Fecha f1(22, 5, 2025);
    cout << "\nEsta disponible el 22/05/2025: ";
    cout << (casa->estaDisponible(f1) ? "Si" : "No") << endl;

    // Prueba 5: Agregar una reserva
    casa->agregarReservacion(f1, 2);
    cout << "Reserva agregada para el 22/05/2025 por 2 noches.\n";

    // Prueba 6: Verificar disponibilidad otra vez
    cout << "Esta disponible el 22/05/2025 ahora: ";
    cout << (casa->estaDisponible(f1) ? "Si" : "No") << endl;

    // Prueba 7: Agregar otra reserva
    Fecha f2(28, 5, 2025);
    casa->agregarReservacion(f2, 3);

    // Prueba 8: Mostrar reservas entre dos fechas
    Fecha desde(20, 5, 2025);
    Fecha hasta(30, 5, 2025);
    cout << "\nReservas entre 20/05/2025 y 30/05/2025:\n";
    casa->mostrarReservasEnRango(desde, hasta);

    // Prueba 9: Simulacion de eliminar reserva
    cout << "\nEliminando reserva con codigo R123 (simulado):\n";
    casa->eliminarReservacion("R123");

    // Prueba 10: Verificar datos basicos
    cout << "\nInformacion del alojamiento:\n";
    cout << "Codigo: " << casa->getCodigo() << endl;
    cout << "Tipo: " << (casa->getTipoAlojamiento() == 0 ? "Casa" : "Apartamento") << endl;
    cout << "Precio por noche: " << casa->getPrecioPorNoche() << endl;

    // Liberar memoria
    delete casa;
    delete anfitrion;

    return 0;
}

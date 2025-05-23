#include <iostream>
#include "Anfitrion.h"
#include "Alojamiento.h"

using namespace std;

int main() {
    // Prueba 1: Crear anfitrión (se genera el código automáticamente)
    Anfitrion* anfitrion1 = new Anfitrion("Laura Torres", 24);
    cout << "Anfitrion creado: " << anfitrion1->getNombreCompleto() << endl;
    cout << "Codigo generado: " << anfitrion1->getDocumentoIdentidad() << endl;

    // Prueba 2: Crear alojamiento
    Alojamiento* casa = new Alojamiento("ALO1", "Casa Verde", "Antioquia", "Guatape", "Cra 8 #15-23", 0, 200000, anfitrion1);
    cout << "\nAlojamiento creado: " << casa->getNombre() << " en " << casa->getMunicipio() << endl;

    // Prueba 3: Agregar amenidades
    casa->agregarAmenidad(0); // Wifi
    casa->agregarAmenidad(2); // Parqueadero
    cout << "\nAmenidades actuales:\n";
    casa->mostrarAmenidades();

    // Prueba 4: Quitar una amenidad
    casa->quitarAmenidad(0); // Quitamos Wifi
    cout << "\nDespues de quitar Wifi:\n";
    casa->mostrarAmenidades();

    // Prueba 5: Verificar disponibilidad antes de reservar
    Fecha f1(22, 5, 2025);
    cout << "\n¿Disponible el 22/05/2025?: ";
    cout << (casa->estaDisponible(f1) ? "Si" : "No") << endl;

    // Prueba 6: Agregar una reserva
    casa->agregarReservacion(f1, 2);
    cout << "Reserva agregada para el 22/05/2025 por 2 noches.\n";

    // Prueba 7: Verificar disponibilidad otra vez
    cout << "¿Disponible el 22/05/2025 ahora?: ";
    cout << (casa->estaDisponible(f1) ? "Si" : "No") << endl;

    // Prueba 8: Agregar otra reserva
    Fecha f2(28, 5, 2025);
    casa->agregarReservacion(f2, 3);

    // Prueba 9: Mostrar reservas entre dos fechas
    Fecha desde(20, 5, 2025);
    Fecha hasta(30, 5, 2025);
    cout << "\nReservas entre 20/05/2025 y 30/05/2025:\n";
    casa->mostrarReservasEnRango(desde, hasta);

    // Prueba 10: Simulación de eliminación
    cout << "\nSimulacion: eliminar reserva con codigo R123:\n";
    casa->eliminarReservacion("R123");

    // Prueba 11: Agregar alojamiento al anfitrión
    anfitrion1->agregarAlojamiento(casa);

    // Prueba 12: Ver reservas desde el anfitrión
    cout << "\nConsultando desde el anfitrion:\n";
    anfitrion1->verReservaciones(desde, hasta);

    // Prueba 13: Mostrar info basica
    cout << "\nResumen del alojamiento:\n";
    cout << "Codigo: " << casa->getCodigo() << endl;
    cout << "Tipo: " << (casa->getTipoAlojamiento() == 0 ? "Casa" : "Apartamento") << endl;
    cout << "Precio por noche: " << casa->getPrecioPorNoche() << endl;

    // Prueba 14: Contadores de recursos
    cout << "\n[INFO] Alojamientos creados: " << Alojamiento::getTotalAlojamientosCreados() << endl;
    cout << "[INFO] Iteraciones en reservas: " << Alojamiento::getTotalIteraciones() << endl;
    cout << "[INFO] Anfitriones creados: " << Anfitrion::getTotalAnfitrionesCreados() << endl;
    cout << "[INFO] Iteraciones en alojamientos: " << Anfitrion::getTotalIteraciones() << endl;

    // Liberar memoria
    delete casa;
    delete anfitrion1;

    return 0;
}

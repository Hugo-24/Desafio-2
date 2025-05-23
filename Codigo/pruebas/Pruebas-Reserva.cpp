#include <iostream>
#include "Fecha.h"
#include "Anfitrion.h"
#include "Alojamiento.h"
#include "Huesped.h"
#include "Reserva.h"

void imprimirBasico(const Reserva& r) {
    std::cout << "Codigo: " << r.getCodigo() << "\n";
    std::cout << "Duracion: " << r.getDuracion() << "\n";
    std::cout << "Metodo: " << r.getMetodoPago() << "\n";
    std::cout << "Monto: " << r.getMonto() << "\n";
    std::cout << "Anotaciones: " << (r.getAnotaciones() ? r.getAnotaciones() : "Ninguna") << "\n";
    Fecha salida = r.calcularFechaSalida();
    std::cout << "Fecha de salida: " << salida.getDia() << "/" << salida.getMes() << "/" << salida.getAnio() << "\n";
}

int main() {
    //Setup inicial
    Anfitrion anfitrion("5555", "Camila Rios", 15);
    Alojamiento alojamiento("A001", "Estudio Sur", "Antioquia", "Envigado", "Calle 12 #34-56", 1, 130000.0, &anfitrion);
    Huesped huesped("Pedro Lopez", "11223344", 10, 4.2);

    // === Constructor automático ===
    std::cout << "\n=== Reserva con constructor automatico ===\n";
    Fecha entrada(20, 8, 2025), pago(15, 8, 2025);
    Reserva r1(entrada, 3, &alojamiento, &huesped, "PSE", pago, 390000.0, "Llega tarde");
    r1.mostrarComprobante();
    imprimirBasico(r1);

    // === Constructor manual (con codigo personalizado) ===
    std::cout << "\n=== Reserva con constructor manual ===\n";
    Reserva r2("R-MANUAL", entrada, 2, &alojamiento, &huesped, "Tarjeta de credito", pago, 260000.0, nullptr);
    r2.mostrarComprobante();
    imprimirBasico(r2);

    // === Copia ===
    std::cout << "\n=== Copia de reserva r1 ===\n";
    Reserva copia(r1);
    copia.mostrarComprobante();

    // === Asignación ===
    std::cout << "\n=== Asignacion r2 = r1 ===\n";
    r2 = r1;
    r2.mostrarComprobante();

    // === Cambios independientes (verificar copia profunda) ===
    std::cout << "\n=== Modificar anotacion de copia ===\n";
    char* notasOriginales = const_cast<char*>(copia.getAnotaciones());
    if (notasOriginales) notasOriginales[0] = '*'; // solo para forzar un cambio (no recomendado en producción)
    std::cout << "Anotaciones modificadas: " << copia.getAnotaciones() << "\n";
    std::cout << "Anotaciones en original: " << r1.getAnotaciones() << "\n";

    return 0;
}

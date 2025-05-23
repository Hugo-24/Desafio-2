#include <iostream>
#include "Fecha.h"
#include "Anfitrion.h"
#include "Alojamiento.h"
#include "Reserva.h"

int main() {
    // 1. Crear un anfitrión ficticio
    Anfitrion anfitrion("A1", "Ana Gómez", 30);

    // 2. Crear un alojamiento vinculado al anfitrión
    Alojamiento alojamiento(
        "AL01",                  // código del alojamiento
        "Cabaña Montaña",        // nombre
        "Cundinamarca",          // departamento
        "La Vega",               // municipio
        "Vereda Sin Salida #5",  // dirección
        2,                        // número de habitaciones
        200000.0,                 // precio por noche
        &anfitrion                // puntero al anfitrión
        );

    // 3. Definir fechas de entrada y pago
    Fecha fechaEntrada(15, 6, 2025);
    Fecha fechaPago(10, 6, 2025);

    // 4. Crear una reserva con código automático
    Reserva reserva(
        fechaEntrada,    // fecha de entrada
        5,               // duración en noches
        &alojamiento,    // puntero al alojamiento
        nullptr,         // puntero al huésped (no implementado aún)
        "TARJETA",      // método de pago
        fechaPago,       // fecha de pago
        1000000.0,       // monto pagado
        "Solicito cama adicional" // anotaciones
        );

    // 5. Mostrar comprobante de la reserva
    reserva.mostrarComprobante();

    // 6. Verificaciones básicas mediante getters
    std::cout << "\n--- Verificaciones Getters ---\n";
    std::cout << "Codigo: " << reserva.getCodigo() << std::endl;
    char* ent = reserva.getFechaEntrada().toString();
    std::cout << "Fecha de entrada: " << ent << std::endl;
    delete[] ent;
    std::cout << "Duracion: " << reserva.getDuracion() << " noches" << std::endl;
    char* salida = reserva.calcularFechaSalida().toString();
    std::cout << "Fecha de salida: " << salida << std::endl;
    delete[] salida;

    return 0;
}

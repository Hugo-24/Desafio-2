#ifndef RESERVA_H
#define RESERVA_H

#include "Fecha.h"

class Alojamiento;
class Huesped;

// Clase que representa una reservación hecha por un huésped.
class Reserva {
private:
    char* codigo;                 // Código del tipo RSV-0001
    Fecha fechaEntrada;          // Fecha de entrada
    int duracion;                // Cantidad de noches
    Alojamiento* alojamiento;    // Alojamiento reservado
    Huesped* huesped;            // Huésped que hizo la reserva
    char* metodoPago;            // "PSE" o "TCredito"
    Fecha fechaPago;             // Fecha del pago
    double monto;                // Valor total pagado
    char* anotaciones;           // Comentarios opcionales (hasta 1000 caracteres)

    // Funciones auxiliares para trabajar con texto sin <cstring>
    int longitudTexto(const char* texto) const;
    void copiarTexto(char* destino, const char* fuente) const;
    char* copiarTexto(const char* fuente) const;
    bool sonIguales(const char* a, const char* b) const;

    // Genera un código del tipo RSV-0001 automáticamente
    void generarCodigo();

    // Contadores de recursos
    static int siguienteId;
    static int totalReservasCreadas;
    static int totalIteracionesEnReservas;

public:
    // Constructor con generación automática de código
    Reserva(const Fecha& fechaEnt, int duracion, Alojamiento* aloj, Huesped* huesp,
            const char* metodoPago, const Fecha& fechaPago, double monto, const char* anotaciones);

    // Constructor con código manual (por ejemplo, al cargar desde archivo)
    Reserva(const char* codigo, const Fecha& fechaEnt, int duracion, Alojamiento* aloj, Huesped* huesp,
            const char* metodoPago, const Fecha& fechaPago, double monto, const char* anotaciones);

    // Constructor de copia
    Reserva(const Reserva& otra);

    // Operador de asignación
    Reserva& operator=(const Reserva& otra);

    // Destructor
    ~Reserva();

    // Métodos de acceso
    const char* getCodigo() const;
    Fecha getFechaEntrada() const;
    int getDuracion() const;
    Alojamiento* getAlojamiento() const;
    Huesped* getHuesped() const;
    const char* getMetodoPago() const;
    Fecha getFechaPago() const;
    double getMonto() const;
    const char* getAnotaciones() const;

    // Devuelve la fecha de salida (entrada + duración)
    Fecha calcularFechaSalida() const;

    // Imprime comprobante de reserva
    void mostrarComprobante() const;

    // Contadores de recursos
    static int getTotalReservasCreadas();
    static int getTotalIteraciones();
};

#endif // RESERVA_H

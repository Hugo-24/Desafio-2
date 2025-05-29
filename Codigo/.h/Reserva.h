#ifndef RESERVA_H
#define RESERVA_H

#include "Fecha.h"

class Alojamiento;
class Huesped;

// Clase que representa una reservación hecha por un huésped.
class Reserva {
private:
    char* codigo;                 // Código tipo RSV-0001
    Fecha fechaEntrada;          // Fecha de entrada
    int duracion;                // Número de noches
    Alojamiento* alojamiento;    // Alojamiento reservado
    Huesped* huesped;            // Huésped que hizo la reserva
    char* metodoPago;            // "PSE" o "TCredito"
    Fecha fechaPago;             // Fecha del pago
    double monto;                // Monto total pagado
    char* anotaciones;           // Comentarios opcionales

    // Generador automático de código
    void generarCodigo();

    // Contadores estáticos de recursos
    static int siguienteId;
    static int totalReservasCreadas;
    static int totalIteracionesEnReservas;

public:
    // Constructor automático (código generado internamente)
    Reserva(const Fecha& fechaEnt, int duracion, Alojamiento* aloj, Huesped* huesp,
            const char* metodoPago, const Fecha& fechaPago, double monto, const char* anotaciones);

    // Constructor manual (por ejemplo, desde archivo)
    Reserva(const char* codigo, const Fecha& fechaEnt, int duracion, Alojamiento* aloj, Huesped* huesp,
            const char* metodoPago, const Fecha& fechaPago, double monto, const char* anotaciones);

    // Constructor de copia
    Reserva(const Reserva& otra);

    // Operador de asignación
    Reserva& operator=(const Reserva& otra);

    // Destructor
    ~Reserva();

    // Getters
    const char* getCodigo() const;
    Fecha getFechaEntrada() const;
    int getDuracion() const;
    Alojamiento* getAlojamiento() const;
    Huesped* getHuesped() const;
    const char* getMetodoPago() const;
    Fecha getFechaPago() const;
    double getMonto() const;
    const char* getAnotaciones() const;

    // Calcula la fecha de salida
    Fecha calcularFechaSalida() const;

    // Mostrar comprobante (por implementar según se requiera)
    void mostrarComprobante() const;

    // Acceso a contadores
    static int getTotalReservasCreadas();
    static int getTotalIteraciones();
    static int getSiguienteId();
    static void setSiguienteId(int nuevoId);
};

#endif // RESERVA_H

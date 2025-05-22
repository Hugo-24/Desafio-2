#ifndef RESERVA_H
#define RESERVA_H

#include "Fecha.h"

class Alojamiento;
class Huesped;

class Reserva {
private:
    static int siguienteId; // contador estático para generar códigos únicos
    char* codigo;
    Fecha fechaEntrada;
    int duracion;
    Alojamiento* alojamiento;
    Huesped* huesped;
    char* metodoPago;
    Fecha fechaPago;
    double monto;
    char* anotaciones; // hasta 1000 caracteres

public:
    // Constructor automático: genera código internamente (RSV-0001, RSV-0002, ...)
    Reserva(const Fecha& fechaEnt, int dur, Alojamiento* aloj, Huesped* huesp,
            const char* metPago, const Fecha& fechaPag, double mto, const char* anot);

    // Constructor completo (para casos especiales)
    Reserva(const char* cod, const Fecha& fechaEnt, int dur, Alojamiento* aloj, Huesped* huesp,
            const char* metPago, const Fecha& fechaPag, double mto, const char* anot);

    Reserva(const Reserva& other);
    Reserva& operator=(const Reserva& other);
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

    // Funciones clave
    Fecha calcularFechaSalida() const;
    void mostrarComprobante() const;
};

#endif // RESERVA_H
